void test(){
	static int var1 = 2;

	var1++;
	printf("var1 = %d\n", var1);
}
int main(int argc, const char *argv[])
{
	int i;
	for (i=0; i<5; i++) {
		test();
	}
	
	return 0;
}
