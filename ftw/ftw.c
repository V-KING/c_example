#include <ftw.h>  
#include <stdio.h>  
#include <sys/stat.h>  
#include <unistd.h>  
  
int fn(const char *fpath, const struct stat *sb, int typeflag);  
int main(int argc, const char *argv[])
{
	if(argc != 2){
		printf("usage: ./ftw dirName\n");
		return -1;
	}
    int temp = ftw(argv[1], fn, 500);  //当返回为0时，表示遍历完成  
	
	if(temp != 0){
		printf("Not walt through all the files\n");  
	}
    return 0;  
}  
  
int fn(const char *fpath, const struct stat *sb, int typeflag)  
{  
    //查看文件是何类型并输出文件设备编号  
    if(typeflag == FTW_F)                             
    {  
        printf("标准文件：\n");  
        printf("dev:%d\n", sb->st_dev);  
    }  
    else if(typeflag == FTW_D)  
    {  
        printf("文件夹路径\n");  
        printf("dev:%d\n", sb->st_dev);  
    }      
    printf("%s\n", fpath);  
    return 0;        //此处如返回不为0的数，程序会终止返回，主程序ftw因此返回，并且返回值相同  
}  
