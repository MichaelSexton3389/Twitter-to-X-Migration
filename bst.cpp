#include "bst.hpp"

BST::BST() {
	root = nullptr;
	size = 0;
}

//using helper destroy function to recursively delete the bst in post-order
BST::~BST() {
	destroy(root);
}

void BST::destroy(XPost *rt){
	if (root == nullptr) {
		return;
	} else {
		destroy(rt->left);
		destroy(rt->right);
		delete rt;
	}
}

XPost* BST::createPost(float time, string content, int likes) 
{
	// creating a new instance of XPost struct
	XPost *newPost = new XPost;
	newPost->postedTime = time;
	newPost->xContents = content;
	newPost->likes = likes;
	newPost->left = nullptr;
	newPost->right = nullptr;
	return newPost;
}

void BST::insertPost(float time, string content, int likes) 
{
	XPost *newPost = createPost(time,content,likes);
	root = insertHelper(root, newPost);
	size += 1;
}

// recursively setting up bst, if posted time is less than root, left, if greater, right, reset root to subtree
XPost* BST::insertHelper(XPost* rt, XPost* pst) 
{
	if (rt == nullptr){
		return pst;
	}
	else if (pst->postedTime > rt->postedTime){
		rt->right = insertHelper(rt->right,pst);
	} else if (pst->postedTime < rt->postedTime){
		rt->left = insertHelper(rt->left,pst);
	}
	return rt;
}

void BST::displayPosts() 
{
	displayHelper(root);
}

void BST::displayHelper(XPost* rt) // Inorder Traversal, some formatting for cout
{
	if (rt->left){
		displayHelper(rt->left);
	}
	cout << rt->postedTime<< ":"<< endl;
	cout <<"__| likes:"<< rt->likes << endl;
	cout <<"__|"<< rt->xContents << endl;
	if (rt->right){
		displayHelper(rt->right);
	}
}

// creating a mostliked post which can be referenced to and returned
XPost* BST::mostPopular() 
{
	XPost *mostLiked = new XPost;
	mostLiked->likes = 0;
	if (root != nullptr){
		mostLiked = root;
	}
	mostPopularHelper(root, mostLiked);
	return mostLiked;
}

//recursively checking new posts against the pre-existing most liked, if the post being checked has more likes than the current mostLiked, assign it to mostLiked
void BST::mostPopularHelper(XPost* rt, XPost*& mostLiked) 
{
	if (rt == nullptr){
		return;
	}
	if (rt->left){
		if (rt->likes > mostLiked->likes){
			mostLiked = rt;
		}
		mostPopularHelper(rt->left, mostLiked);
	}
	if (rt->right){
		if (rt->likes > mostLiked->likes){
			mostLiked = rt;
		}
		mostPopularHelper(rt->right, mostLiked);
	}
}
