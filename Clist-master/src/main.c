/* 
* by vk@20170816
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "list.h"


#if 0
#define print_dbg(fmt, arg...)
#define print_info(fmt, arg...)
#define print_err(fmt, arg...)
#else
#define print_dbg(fmt, arg...)      printf("\033[36m[DBG ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_info(fmt, arg...)     printf("\033[32m[INFO][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_err(fmt, arg...)      printf("\033[31m[ERR ][%s: %s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##arg);
#define print_pAddr(p1, p2)         printf("\033[37m[Addr compare][%s: %s:%d][0x%x :: 0x%x]\n", __FILE__, __FUNCTION__, __LINE__, p1,p2);
#endif

#ifdef INVG_RELEASE
#define print_dbg(fmt, arg...)
#define print_info(fmt, arg...)
#define print_err(fmt, arg...)
#define print_pAddr(p1, p2)
#endif


LIST_DEF(Int_List)
	int data;
LIST_DEF_END(Int_List)

Int_List* Create_Int_List(int k) {
	MALLOC(Int_List, obj);
	obj->data = k;
	LIST_CREATE_INIT(obj);
	return obj;
}
/*
 * @bref: order add new_node from min to max
 * @l: list
 * @new_node: according to new_node->data to sort,
 * 		so, when u need to add you own data,change 
 * 		'Int_List' to your own type
 */
void list_order_add(list *l, Int_List *new_node){
	int delt;
	list_node *p,*n;
	if(list_empty(l)){
		list_add(l, (list_node*)new_node);	
		return;
	}
	list_for_each(Int_List*, i, l){
		list_node * temp= (list_node*)i;
		p = temp;
		n = temp->next;
		Int_List *pd = (Int_List *)p;
		Int_List *nd = (Int_List *)n;
		if(new_node->data <= pd->data){
			list_add(l,new_node);
			l->head = l->head->prev;
			return;
		}else{
			if(new_node->data <= nd->data){
				list_insert(p, new_node);
				return;
			}else if(n->next==l->head){//all data in the list is small than new_node->data, add to tail.
				list_add(l, new_node);
				return;
			}
		}
	} for_each_end
}

/*
 * @return:
 * 		NULL, if not find in the list
 * 		Int_List*, return finded Node
 */
Int_List* list_Int_List_find(list *l, int data)  {  
	Int_List *pNode; 
	if(NULL == l || NULL == l->head) { 
		return NULL;
	}
	list_for_each(Int_List *, i, l ){
		pNode = i;
		if(i->data == data){
			return pNode;
		}
	} for_each_end
	if(pNode->node.next == l->head){
		return NULL;
	}
	return pNode;
}  
/*
 * TODO: free delete head node,after used
 */
list_node* take_head_data(list *l){
	list_node *pNode;
	list_node *origHead = l->head;
	list_node *origHead_prev = origHead->prev;
	// head move to next
	l->head = origHead->next;
	/* remove origin head*/
 	l->head->prev = origHead_prev;
	origHead_prev->next = l->head;
	return origHead;
}

/*
 * @return : if not finde in the list,then return NULL,
 * 		else return the Int_List* pNode
 */
Int_List *list_Int_List_remove(list *l, int data){
	list_node *pNode;
	
	pNode = (list_node *)list_Int_List_find(l,data);
	if(pNode = l->head){
		return take_head_data(l);
	}
	if(NULL == pNode){
		return NULL;
	}
	list_node *p = pNode->prev;
	list_node *n = pNode->next;
	p->next = n;
	n->prev = p;
	return pNode;
}

void listDeleteAll_Int_List(list *l){
    /*************method 1:*****************/
    if(NULL==l || NULL==l->head){
        return;
    }
    list_for_each(Int_List*, i, l){
        if(i->node.next == l->head){
            l->head = NULL;
            print_err("1\n");
        }
        print_err("i=%d\n", i->data);
        memset(i, 0, sizeof(Int_List));
        free(i);
    }for_each_end
    return;
    /*************method 2:*****************/
	if(NULL==l || NULL==l->head){
		return;
	}
	Int_List *i;
	list_node *pos;
	list_node *head =l->head;
	list_node *tail = l->head->prev;
	char b;
	for(pos = head, i = (Int_List *)pos, b=1;
		(pos != head)||b;	
	){
		list_node *p = tail;// or list_node *p = pos->next;
		list_node *n = pos->next;
		i = (Int_List *)pos;
		//print_err("rm[data ,p   ,pos,n        ]=[%02d,0x%x,0x%x,0x%x]\n",i->data,p , pos  , n);
		p->next = n; 
		n->prev = p;  
		
		if (pos == pos->next) {
            print_err("tail node\n");
            // TODO: destruct(i)
            free(i);//  After free i, U can't use i
			l->head = NULL;
			break;
		}
		pos = pos->next,  b = 0;
		// TODO: destruct(i)
		free(i);//  After free i, U can't use i
	}
}

#define list_find_loop(type, data) \
    type *pNode; \
    list_for_each(type *, i, l ){\
        pNode = i;\
        if(i->data == data){\
            break;\
        }\
    } for_each_end \
    if(pNode->node.next == l->head){\
        return NULL;\
    }\
    return pNode;\
    
#define list_find_loop_end()
/*
 * @brief: look list_Int_List_find()
 */
Int_List* list_find_byXX(list *l,int data)  {  
    if(NULL == l || NULL == l->head) { 
        return NULL;
    }
    list_find_loop(Int_List, data)
    list_find_loop_end()
}  


list* l;
#if 1
int main() {
    print_dbg("### Begin..\n");
	l = Create_List();
	list_order_add(l, Create_Int_List(9));
	list_order_add(l, Create_Int_List(1));
	list_order_add(l, Create_Int_List(7));
	list_order_add(l, Create_Int_List(5));
	list_order_add(l, Create_Int_List(3));
	list_order_add(l, Create_Int_List(4));
	list_order_add(l, Create_Int_List(5));
	list_order_add(l, Create_Int_List(12));
	list_order_add(l, Create_Int_List(11));
	Int_List *d1 = Create_Int_List(10);
	printf("d1 = 0x%x\n",d1);
	list_order_add(l, d1);
    
	print_info("1. show list:\n");
	list_for_each(Int_List* , i, l) {
		printf("%d\n", i->data);
	} for_each_end
    print_info("#######################################################################\n\n");

	
    print_info("2. take_head_data...\n");
	take_head_data(l);
	take_head_data(l);
	print_info("After take 2 head:\n");
	list_for_each(Int_List* , i, l) {
		printf("%d\n", i->data);
	} for_each_end
    print_info("#######################################################################\n\n");
		
    
    print_info("3. After list_Int_List_find(l, 10) : \n");
	printf("d2 = 0x%02x\n",list_Int_List_find(l, 10));
	printf("d3 = 0x%02x\n",list_find_byXX(l, 10));
    print_info("#######################################################################\n\n");

    //find nothing
    print_info("4. find nothing data=111 whitch not in list :\n");
    printf("d2 = 0x%02x\n",l);
    printf("d2 = 0x%02x\n",l->head);
    printf("d2 = 0x%02x\n",l);
    printf("d2 = 0x%02x\n",(list *)l->head);
    printf("d2 = 0x%02x\n",list_Int_List_find(l, 111));
    printf("d2 = 0x%02x\n",list_find_byXX(l, 111));
    print_info("#######################################################################\n\n");   
    
	//remove
	print_info("5. list_Int_List_remove test :\n");
	Int_List *p = list_Int_List_remove(l, 4);
	print_info("l            =0x%x\n", l);
	print_info("l->head      =0x%x\n", l->head);
	print_info("p            =0x%x\n", p);
	print_info("l->head->next=0x%x\n", l->head->next);
	print_info("l->head->prev=0x%x\n", l->head->prev);
	list_for_each(Int_List* , i, l) {
		printf("%d\n", i->data);
		print_info("[p ,pos  ,n        ]=[0x%x,0x%x,0x%x]\n",pos->prev, pos  , pos->next);
	} for_each_end
    print_info("#######################################################################\n\n");
	
	printf("7. listDeleteAll_Int_List(l) test:\n");
	listDeleteAll_Int_List(l);
    printf("After listDeleteAll_Int_List(l) :\n");
	if(!list_empty(l)){
		list_for_each(Int_List* , i, l) {
			printf("%d\n", i->data);
		} for_each_end
	}
	print_info("#######################################################################\n\n");
	
	
    print_dbg("### End....\n");
    return 0;
}
#endif
