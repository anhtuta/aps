
package pink_and_blue;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

/*
 * Bài PinkAndBlue
Chú ý: bài này input quá dài và quá lớn: file input gồm hơn 300 nghìn dòng,
có test case có 34000 đỉnh và 85000 cạnh, nên lưu = mảng ko đủ bộ nhớ
*/
 **/
public class PinkAndBlue {
	final int MAX = 100001;
	final int PINK = 0;
	final int BLUE = 1;
	final int INF = 999999;
	
	int T;
	int n;	//số lượng học sinh (hs)
	int m;	//số lượng mối quan hệ bạn bè
	char gender[];
	int color[];	//màu áo của các hs
	LinkedList friends[];	//friends[k] = danh sách các bạn bè của k
	int currInversion, minInversion;
	Queue q;
	Scanner sc;
	
	public void input() {
		n = sc.nextInt();
		m = sc.nextInt();
		currInversion = 0;
		minInversion = INF;
		
		gender = new char[n+1];
		friends = new LinkedList[n+1];
		color = new int[n+1];
		
		for (int i = 1; i <= n; i++) {
			gender[i] = sc.next().charAt(0);
			friends[i] = new LinkedList();
			color[i] = -1;
		}
		
		int u,v;
		for (int i = 1; i <= m; i++) {
			u = sc.nextInt();
			v = sc.nextInt();
			friends[u].add(v);
			friends[v].add(u);
		}
		
		q = new Queue();
	}
	
	void resetColor() {
		for (int i = 1; i <= n; i++) {
			color[i] = -1;
		}
	}

	boolean pinkAndBlue() {
		for (int i = 0; i <= 1; i++) {
			resetColor();
			currInversion = 0;
			color[1] = i;	//gán màu cho hs đầu tiên
			q.initQueue();
			q.enQueue(1);		//cho học sinh đầu tiên vào queue
			int neigh;

			while (!q.isQueueEmpty()) {
				//lấy hs hiện tại trong queue ra
				int currHs = q.deQueue();

				//xét các bạn bè của currHs và tô màu cho nó
				Node p = friends[currHs].head;
				while(p != null) {
					neigh = p.data;
					if (color[neigh] == -1) {
						color[neigh] = 1 - color[currHs];
						q.enQueue(neigh);
					} else if (color[neigh] == color[currHs]) return false;
					p = p.next;
				}
				
			}

			for (int k = 1; k <= n; k++)
			{
				if (color[k] == PINK && gender[k] == 'B') currInversion++;
				else if (color[k] == BLUE && gender[k] == 'G') currInversion++;
			}
			if (minInversion > currInversion) minInversion = currInversion;
		}
		
		return true;
	}
	
	public static void main(String[] args) throws FileNotFoundException {
		PinkAndBlue pab = new PinkAndBlue();
		System.setIn(new FileInputStream("PinkAndBlue_input.txt"));
		pab.sc = new Scanner(System.in);
		
		pab.T = pab.sc.nextInt();
		for (int tc = 1; tc <= pab.T; tc++) {
			pab.input();
			if (pab.pinkAndBlue())
				System.out.println(pab.minInversion);
			else System.out.println("-1");
		}
	}
	

	//*=========== DATA STRUCTURES ============*//

	class Node {
		int data;
		Node next;
		
		public Node(int d) {
			this.data = d;
			next = null;
		}
	}
	
	/*
	 * Danh sách liên kết lưu các phần tử kiểu Node
	 */
	class LinkedList {
		Node head;	//head = thằng đầu tiên của DSLK
		int length;
		
		public LinkedList() {
			head = null;
			length = 0;
		}
		
		public void add(int data) {
			Node d = new Node(data);
			if(head == null) {
				head = d;
			} else {
				d.next = head;
				head = d;
			}
			length++;
		}
		
	}

	/*
	 * Hàng đợi lưu các phần tử kiểu int
	 */
	class Queue {
		int front, rear;
		int myQueue[];
		
		public Queue() {
			front = rear = -1;
			myQueue = new int[100000];
		}
		
		void initQueue() {
			front = rear = -1;
		}
		void enQueue(int data) {
			rear++;
			myQueue[rear] = data;
		}
		int deQueue() {
			front++;
			int temp = myQueue[front];
			if(front==rear) front=rear=-1;
			return temp;
		}
		boolean isQueueEmpty() {
			return front==-1 && rear==-1;
		}
	}
}

