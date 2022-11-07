package addressbook;
import java.util.*;

//Define node
class Node <T,U>
{
	static final int black = 0;
	static final int red = 1;
	// holds the key
	T name;
	// holds the key
	U office; 
	// pointer to the parent
	Node<T, U> parent;
	// pointer to left child
	Node <T,U> left; 
	// pointer to right child
	Node <T,U> right;
	// 0 for Black and 1 for Red
	public int color;
	Node()
	{
		this.name = null;
		this.office = null;
		this.parent = null;
		this.left = null;
		this.right = null;
		// Every leaf is black according to RB rules
		this.color = black;
	}
	Node(T name, U office)
	{
		this.name = name;
		this.office = office;
		this.parent = null;
		this.left = null;
		this.right = null;
		// According to RB rules, default color is black
		this.color = black;
	}
}

	public class AddressBookTree <T extends Comparable <T>,U>
	{
		static final int black = 0;
		static final int red = 1;
		private Node<T,U> root;
		private Node<T,U> nil;
	
		// Default constructor
		public AddressBookTree()
		{
			this.nil = new Node <T, U>();
			this.nil.name = null;
			this.nil.office = null;
			this.nil.parent = null;
			this.nil.left = null;
			this.nil.right = null;
			this.nil.color = black;
			this.root = nil;
		}
		public void insert(T name, U office)
		{
			Node<T,U> z = new Node<T,U>(name,office);
			Node<T,U> x = this.root;
			Node<T,U> y = this.nil;
			while (x != this.nil)
			{
				y = x;
				// Compare if value is bigger or smaller than current node
				// To be placed right or left
				if (z.name.compareTo(x.name) < 0)
				{
					x = x.left;
				} 
				else
				{
					x = x.right;
				}
			}
				// y is parent of x
			z.parent = y;
			if (y == this.nil)
			{
				this.root = z;
			} 
			else if (z.name.compareTo(y.name) < 0) 
			{
				y.left = z;
			} 
			else
			{
				y.right = z;
			}
			z.left = this.nil;
			z.right = this.nil;
			z.color = red;
			Insertfixup(z);
		}
		// Inspired by Dr. Steinburg's pseudocode from RB-Trees.pdf
		// Ensure that RB tree follows rules when inserting
		public void Insertfixup(Node<T, U> z) 
		{
			Node<T,U> y;
			while (z.parent.color == red)
			{
				if (z.parent == z.parent.parent.left)
				{
					y = z.parent.parent.right;
					// Case 1: z's uncle is red
					if (y.color == red)
					{
						z.parent.color = black;
						y.color = black;
						z.parent.parent.color = red;
						z = z.parent.parent;
					} 
					else
					{
						// Case 2: z's uncle is black and z is right child
						if (z == z.parent.right)
						{
							z = z.parent;
							leftRotate(z);
						}
						// Case 3: z's uncle is black and z is left child
						z.parent.color = black;
						z.parent.parent.color = red;
						rightRotate(z.parent.parent);
					}
				} 
				else
				{
					y = z.parent.parent.left;
		
					if (y.color == red) 
					{
						y.color = black;
						z.parent.color = black;
						z.parent.parent.color = red;
						z = z.parent.parent;	
					}
					else 
					{
						if (z == z.parent.left) 
						{
							z = z.parent;
							rightRotate(z);
						}
						z.parent.color = black;
						z.parent.parent.color = red;
						leftRotate(z.parent.parent);
					}
				}
			}
		// Root needs to be right according to RB rules
			this.root.color = black;
		}
			
		//Inspired by Dr. Steinburg's pseudocode from RB-Trees.pdf
		public void rbTransplant(Node<T, U> u, Node<T, U> v)
		{
			if (u.parent == this.nil)
			{
				this.root = v;
			}
			else if (u == u.parent.left)
			{
				u.parent.left = v;
			}
			else
			{
				u.parent.right = v;
			}
			v.parent = u.parent;
			
		}
		
			// Inspired by Dr. Steinburg's pseudocode from RB-Trees.pdf
			// Rotate left at x node
			public void leftRotate(Node <T,U> x) {
				Node <T,U> y = x.right;
				// Turn y's left subtree into x's right subtree
				x.right = y.left;
				if (y.left != this.nil) 
				{
					y.left.parent = x;
				}
				//Link x's parent to y
				y.parent = x.parent;
				if (x.parent == this.nil) 
				{
					this.root = y;
				} 
				else if (x == x.parent.left) {
					x.parent.left = y;
				}
				else {
					x.parent.right = y;
				}
				// Put x on y's left
				y.left = x;
				x.parent = y;
			}
	
			// rotate right at node x
			public void rightRotate(Node <T,U> x) {
				Node <T,U> y;
				y = x.left;
				// Turn y's right subtree into x's left subtree
				x.left = y.right;
				if (y.right != null)
				{
					y.right.parent = x;
				}
				//Link x's parent to y
				y.parent = x.parent;
				if (x.parent == this.nil)
				{
					this.root = y;
				}
				else if (x == x.parent.right)
				{
					x.parent.right = y;
				} 
				else
				{
					x.parent.left = y;
				}
				// Put x on y's right
				y.right = x;
				x.parent = y;
			}
			
	// Traverse tree to find key		
	Node <T,U> search (T name)
	{
		Node<T,U> key = this.root;
		while (key != this.nil)
		{
			if (name.compareTo(key.name) == 0)
			{
				return key;
			}
	
			if (name.compareTo(key.name) < 0)
			{
				key = key.left;
			} 
			else 
			{
				key = key.right;
			}
		}
		return key;
	}
	
	// Delete node at with name
	public void deleteNode(T name) {
		Node <T,U> z = search(name);
		Node <T,U>x = this.nil;
		Node <T,U> y;
		y = z;
		int yOC = y.color;
		if (z.left == this.nil)
		{
			x = z.right;
			rbTransplant(z, z.right);
		}
		else if (z.right == this.nil)
		{
			x = z.left;
			rbTransplant(z, z.left);
		} 
		else
		{
			y = treemin(z.right);
			yOC = y.color;
			x = y.right;
			if (y.parent == z)
			{
				x.parent = y;
			} 
			else
			{
				rbTransplant(y, y.right);
				y.right = z.right;
				y.right.parent = y;
			}
			rbTransplant(z, y);
			y.left = z.left;
			y.left.parent = y;
			y.color = z.color;
		}
		if (yOC == black)
		{
			Deletefixup(x);
		}
	}
	
	// Find minimum value of tree
	public Node<T, U> treemin(Node<T, U> root) 
	{
		Node <T,U> node = root;
		while (node.left != this.nil) 
		{
			node = node.left;
		}
		return node;
	}
	
	//Inspired by Dr. Steinburg's pseudocode from RB-Trees.pdf
	// Ensures that deletion will keep the tree following rb rules
	private void Deletefixup(Node<T, U> x)
	{
		Node <T,U> w = new Node<T,U>();
		while (x != this.root && x.color == black) 
		{
			if (x == x.parent.left) 
			{
				w = x.parent.right;
				
				// Case 1
				if (w.color == red)
				{
					w.color = black;
					x.parent.color = red;
					leftRotate(x.parent);
					w = x.parent.right;
				}
				
				// Case 2
				if (w.left.color == black && w.right.color == black)
				{
					w.color = red;
					x = x.parent;
				} 
				else
				{
					// Case 3
					if (w.right.color == black)
					{
						w.left.color = black;
						w.color = red;
						rightRotate(w);
						w = x.parent.right;
					}
					
					// Case 4
					w.color = x.parent.color;
					x.parent.color = black;
					w.right.color = black;
					leftRotate(x.parent);
					x = this.root;
				}
			}
			else 
			{
				w = x.parent.left;
				if (w.color == red)
				{
					w.color = black;
					x.parent.color = red;
					rightRotate(x.parent);
					w = x.parent.left;
				}
	
				if (w.right.color == black && w.left.color == black) 
				{
					w.color = red;
					x = x.parent;
				} 
				else
				{
					if (w.left.color == black) 
					{
						w.right.color = black;
						w.color = red;
						leftRotate(w);
						w = x.parent.left;
					} 
					w.color = x.parent.color;
					x.parent.color = black;
					w.left.color = black;
					rightRotate(x.parent);
					x = this.root;
				}
			} 
		}
		x.color = black;
		
	}
	
	// Displays tree in order
	public void display()
	{
		Inorder(getRoot());
	}
	
	// Prints tree inorder
	private void Inorder(Node <T,U> node)
	{
		if (node != this.nil)
		{
			Inorder(node.left);
			System.out.printf("%22s %12s %d \n" ,node.name, node.office, node.color);
			Inorder(node.right);
		} 
	}
	
	// Count the number of black nodes in tree
	public int countBlack(Node<T,U> node)
	{
		int count = 0;
		if(node == this.nil)
		{
			return 0;
		}
		count += countBlack(node.left);
		count += countBlack(node.right);
		// Ensure that no nil nodes is being counted
		if (node.color == black && node.office != null)
		{
			count++;
		}
		return count;
		
	}
	
	// Counts red nodes in tree
	public int countRed(Node<T,U> node)
	{
		int count = 0;
		if(node == this.nil)
		{
			return 0;
		}
		count += countRed(node.left);
		count += countRed(node.right);
		if(node.color == red)
		{
			count++;
		}
		return count;
		
	}
	
	public Node<T,U> getRoot()
	{
		return root;
	}
	
	public void setRoot(Node<T,U> root) {
	this.root = root;
	}
	
	}
	
