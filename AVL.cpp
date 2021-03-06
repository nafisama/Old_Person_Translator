
/**************************************************************/
/* Part 1:                                                    */ /* Name the methods below with the correct name from the list */
/* below:                                                     */
/*    find                                                    */
/*    insert                                                  */
/*    printTreePre                                            */
/*    printTreeIO                                             */
/*    printTreePost                                           */
/*                                                            */
/* Once you have named them, move them to into the AVL Class  */
/* Definition file (the .cpp), below the constructors (scroll */
/* down and you'll see the constructors)                      */
/**************************************************************/
/********************* method 1 *******************************/

/*******************End of Naming Methods*********************/
/* Now move the methods above (with the blanks filled in     */
/* correctly below the constructors, below                   */
/*************************************************************/

/*************************************************************/
/*Part 2                                                     */
/* Now you must do two things:                               */
/* 1) add a count to the find method such that it counts how */
/*    many comparisions you do every time you find an        */
/*    abbreviation; and                                      */
/* 2) in the insert method, add a call to the setHeight      */
/*    method in the appropriate place(s) so that after you   */
/*    inserted, the setHeight method adjusts the heights of  */
/*    the inserted node's ancestors.
/*************************************************************/

/*************************************************************/
/*Part 3                                                     */
/* Write the methods (in red, below) that are part of the    */
/* AVL Tree class                                            */
/*************************************************************/

#include "AVL.hpp"

#include <iostream>
#include <stdlib.h>
using namespace std;

/*************************************************************/
/* Constructors
   debug is a boolean flag that, if set, will result in the
   printing of a number of debug statements.  If it isn't
   set, the code will print without the debug statements.
*/
AVL::AVL() {
	root = NULL;
	debug = false;
}

AVL::AVL(bool debflag) {
	root = NULL;
	debug = debflag;
}

AVL::AVL(string ab, string d) {
	root = new TNode(ab, d, false);
	debug = false;

}

AVL::AVL(string ab, string d, bool debflag) {
	root = new TNode(ab, d, debflag);
	debug = debflag;

}
void AVL::printTreePre(TNode *tmp) {
	if (tmp == NULL) {
		return;
	}
	else {
		tmp->printNode(debug);
		printTreePre(tmp->left);
		printTreePre(tmp->right);
	}
}
/********************* method 2 *******************************/
void AVL::printTreePost(TNode *tmp) {
	if (tmp == NULL) {
		return;
	}
	else {
		printTreePost(tmp->left);
		printTreePost(tmp->right);
		tmp->printNode(debug);
	}
}
/********************* method 3 *******************************/
TNode *AVL:: find(string a) {
	int ct=0;
	if (root == NULL) {
		if (debug) {
		   cout << "root is null " << a << endl;
		}
		return NULL;
	}
	else {
		TNode *tmp = root;
		while (tmp != NULL) {
			if (debug) {
				cout <<tmp->abbr << " and "<<a << endl;
				ct++;
			}
			if (a < tmp->abbr) {
				if (debug) {
					cout << "going left " << endl;
				}
				if (tmp->left == NULL) {
					return NULL;
				}
				else {
					tmp=tmp->left;
					//ct++;
				}
			}
			else if (a > tmp->abbr) {
				if (debug) {
					cout << "going right " << endl;
				}
				if (tmp->right == NULL) {
					return NULL;
				}
				else {
					tmp=tmp->right;
					//ct++;
				}
			}
			else {
				if (debug) {
					cout << " in " << ct << endl;
				}
				return tmp;
			}
		//ct++;
		}
	}
	return NULL;
}
/********************* method 4 *******************************/
void AVL::printTreeIO (TNode *tmp) {
	if (tmp == NULL) {
		return;
	}
	else {
		printTreeIO(tmp->left);
		tmp->printNode(debug);
		printTreeIO(tmp->right);
	}
}
/********************* method 5 *******************************/
bool AVL:: insert(string ab, string d) {
	TNode *newnode = new TNode(ab, d, debug);

	if (root == NULL) {		
		if (debug ) {
		    cout << "root NULL" << endl;
		}
		root = newnode;
		setHeight(newnode);
		cout<< root->abbr <<endl;
		return true;
	}
	else {
		TNode *tmp = root;
		while (tmp != NULL){
			if (newnode->abbr < tmp->abbr) {

				if (tmp->left == NULL) {
					tmp->left = newnode;
					tmp->left->parent = tmp;
					setHeight(tmp->left);
					return true;
				}
				else {
					tmp=tmp->left;

				}
			}
			else if (newnode->abbr > tmp->abbr) {

				if (tmp->right == NULL) {
					tmp->right = newnode;
					tmp->right->parent = tmp;

					setHeight(tmp->right);
					return true;
				}
				else {
					tmp=tmp->right;

				}
			}
			else {
				return false;
			}
		}
	}
	return false;
}
/*************************************************************/
/*Methods you have to write                                  */
/*These methods are specifically for an AVL tree, which means*/
/*they involve keeping track of a node's height and balance, */
/*and rotating when a node becomes unbalanced                */
/*WATCH OUT FOR:                                             */
/*   NULL nodes (they don't have fields                      */
/*   Attaching parents properly, especially during rotations */
/*************************************************************/
int AVL::getBalance(TNode *tmp) {
/* method that finds the balance of a node tmp and returns that balance as an int
*/
	int h;
	if(tmp->left !=NULL && tmp->right !=NULL){
		h=tmp->left->height - tmp->right->height;
	}else if(tmp->left==NULL && tmp->right ==NULL){
		h=0;
	}
	else if(tmp->left==NULL){
		h=0 - tmp->right->height;
	}else if(tmp->right ==NULL){
		h=tmp->left->height;
	}else{
		h=0;
	}
	return h;
}

TNode *AVL::rotateRight(TNode *UN) {
/* rotates right around node tmp and returns the node rotated up.
 * Note: this method must reset the heights of the node rotated down and the nodes rotated up,
 * and you must reset the heights of all nodes that are ancestors of the node rotated down.
 * You will also need to reattach the newly rotated up node to the rest of the tree either in this method or in setheights.
*/


			TNode *LC =UN->left;
		    TNode *LC_right= LC->right;

		    //LEFT ROTATION
		    if(LC !=NULL && LC_right !=NULL ){

		            LC->right=UN;
		            UN->left=LC_right;
		            LC_right->parent=UN;

		            if(UN->parent==NULL){
		            	root=LC;
		            	LC->parent=NULL;
		            }else{
		            	LC->parent=UN->parent;
		            	if(UN->parent->right==UN){
		            		     UN->parent->right=LC;
		            	}else{
		            		      UN->parent->left=LC;
		            		}
		            	}

		            UN->parent=LC;
		            setHeight(LC_right);
		    }
		    else{
		    	//when LC_right is null

		            LC->right=UN;
		            UN->left=NULL;

		            if(UN->parent==NULL){
		            	root=LC;
		            	LC->parent=NULL;
		            }else{
		            	LC->parent=UN->parent;

		            	if(UN->parent->right==UN){
		            		UN->parent->right=LC;
		            	}else{
		            		UN->parent->left=LC;
		            	}
		            }

		            UN->parent=LC;
		            UN->left=NULL;

		            //Setting Height
		             setHeight(UN);
		    }


		        return LC;


}

TNode *AVL::rotateLeft(TNode *UN) {
/* rotates down around node tmp and returns the node rotated up.  Note: this method must reset the heights of the node rotated down and the nodes rotated up, and you must reset the heights of all nodes that are ancestors of the node rotated down. You will also need to reattach the newly rotated up node to the rest of the tree either in this method or in setheights.
*/
	 	TNode *RC =UN->right;
	    TNode *RC_left= RC->left;

	    //LEFT ROTATION
	    if(RC !=NULL && RC_left !=NULL ){

	            RC->left=UN;
	            UN->right=RC_left;
	            RC_left->parent=UN;

	            if(UN->parent == NULL){
	            	root=RC;
	           	 	RC->parent=NULL;

	            }else{
	           		 RC->parent=UN->parent;
	           		if(UN->parent->left == UN){
	           		  UN->parent->left=RC;
	           		}else{
	           			UN->parent->right=RC;
	           		}
	           	 }
	            UN->parent=RC;

	            setHeight(RC_left);

	    }else{  //when RC_left is null
	    	//cout<<"Rc_left is null "<<RC->abbr<<endl;

	            RC->left=UN;
	            UN->right=NULL;
	            if(UN->parent == NULL){ //UN is root
	            	root=RC;
	            	RC->parent=NULL;
	            }else{
	            	 RC->parent=UN->parent;
	            	 if(UN->parent->left == UN){
	            		 UN->parent->left=RC;
	            	 }else{
	            		 UN->parent->right=RC;
	            	 }
	            }

	            UN->parent=RC;
	            UN->right=NULL;

	            setHeight(UN);

	    }


	      return RC;
}

void AVL::setHeight(TNode *tmp) {
/*
	This method sets the height of tmp and then of all the ancestors of tmp.
 It stops when the height of a node does not change.
 Note that this method most likely calls getBalance and possibly the rotate methods,
 and may even set the newly rotated up node's parent attachement,
 although you could do that in the rotate method.
*/ 
int prev=0;  // previous height

int balance;
while(tmp!=NULL){

	if(tmp->left == NULL && tmp->right == NULL){
		//NO CHILDREN
		tmp->height=1;
	}else if(tmp->left !=NULL && tmp->right!=NULL){
		//BOTH CHILDREN
		tmp->height= (tmp->left->height >= tmp->right->height )? tmp->left->height +1 : tmp->right->height +1;

	}else if(tmp->left ==NULL){
		//1 CHILD, LEFT=NULL
		tmp->height = tmp->right->height +1 ;

	}else {
		// RIGHT IS NULL
		tmp->height= tmp->left->height +1 ;


	}

			balance= getBalance(tmp);
			//cout<< balance <<endl;
			if(balance == -2 && getBalance(tmp->right) ==-1){
				//left
				rotateLeft(tmp);

			}else if(balance >=2 && getBalance(tmp->left)==1){
				//right
				rotateRight(tmp);

			}else if(balance <=-2 && getBalance(tmp->right) ==1 ){
				//left - right

				rotateRight(tmp->right);

			}else if(balance >= 2 && getBalance(tmp->left) == -1){
				//right - left

				rotateLeft(tmp->left);

			}else{
				//NO rotation, balance ==0

			}



			if(prev==tmp->height){  //node's height is unchanged
				//cout<<"height remain unchanged if "<<endl;
				break;
			}

			tmp=tmp->parent;
			if(tmp!=NULL){
				prev=tmp->height;

			}
	}


}
void AVL::printTreeIO() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing In Order:" <<endl;
		printTreeIO(root);
	}
}

void AVL::printTreePre() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PreOrder:" <<endl;
		printTreePre(root);
	}
}

void AVL::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PostOrder:" <<endl;
		printTreePost(root);
	}
}

void AVL::clearTree() {
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}
void AVL::clearTree(TNode *tmp) {
	if (tmp == NULL) {
		return;
	}
	else {
		clearTree(tmp->left);
		clearTree(tmp->right);
		tmp->printNode();
		delete(tmp);
	}
}
