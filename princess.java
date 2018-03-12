/*
Mê cung là matrix n*n (n<200). Trong 1 ô có 1 trong 3 giá trị:
	0: nếu ô đó là cạm bẫy
	1: nếu ô đó an toàn
	2: nếu ô đó có công chúa
Chỉ có duy nhất 1 ô có công chúa. Hoàng tử ở ô (1,1), hãy tìm đường đi ngắn nhất để giải cứu công chúa khỏi mê cung (lối thoát ở ô (n,n));

input mẫu:
5
4
1 0 1 1
1 1 2 0
0 1 0 1
1 0 1 1
5
1 0 1 1 0
1 0 0 0 0
1 1 2 1 1
1 1 1 0 1
1 0 1 0 1
6
1 1 0 2 1 1
0 1 0 1 0 1
0 1 0 1 0 1
0 0 0 1 0 1
0 0 0 1 0 1
1 1 1 1 0 1
5
1 1 0 1 0
1 0 2 1 1
1 0 1 1 1
1 1 1 0 1
1 1 1 0 1
10
1 0 1 1 1 1 1 1 1 1
1 0 1 0 0 0 0 0 0 1
1 0 1 0 1 1 1 1 0 1
1 0 1 0 1 0 0 1 0 1
1 0 1 0 1 0 0 1 0 1
1 0 1 0 1 2 0 1 0 1
1 0 1 0 0 0 0 1 0 1
1 0 1 1 1 1 1 1 0 1
1 0 0 0 0 0 0 0 0 1
1 1 1 1 1 1 1 1 1 1

output:
-1
8
-1
12
98

Cách làm: 
Ban đầu nhét ô bắt đầu vào queue
ở mỗi vòng lặp lấy ô khỏi queue và nhét các hàng xóm vào queue, đồng thời cập nhập đường đi ngắn
nhất từ ô bắt đầu đến ô vừa nhét vào queue
*/

package hello;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Solution {
	int T;
	int n;
	int [][]a;
	Scanner sc;
	Queue<Point> q = new Queue<Point>(100000);
	int moveX[] = {0, 0, -1, 1};
	int moveY[] = {1, -1, 0, 0};
	int [][]mark;
	
	public void reset() {
		mark = new int[n+1][n+1];
		this.q.destroy();
	}
	
	public void input() {
		n = sc.nextInt();
		a = new int[n+1][n+1];
		mark = new int[n+1][n+1];
		
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				a[i][j] = sc.nextInt();
				mark[i][j] = 0;
			}
		}
	}
	
	public boolean isSafePosition(int x, int y) {
		if(x >= a[0].length || x < 1 || y >= a[0].length || y < 1) return false;
		return a[x][y] != 0 && mark[x][y] == 0;
	}
	
	public void printMark() {
		System.out.println("Print mark:");
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if(mark[i][j] < 10) {
					System.out.print(mark[i][j] + "   ");
				} else if(mark[i][j] < 100) {
					System.out.print(mark[i][j] + "  ");
				} else {
					System.out.print(mark[i][j] + " ");
				}
			}
			System.out.println();
		}
		System.out.println();
	}
	
	public int princess(int startX, int startY) {
		Point pStart = new Point(startX, startY);
		q.enQueue(pStart);
		while(!q.isEmpty()) {
			Point currPoint = q.deQueue();
			int currX = currPoint.x;
			int currY = currPoint.y;
			
			if(a[currX][currY]==2) {
				return mark[currPoint.x][currPoint.y];
			}
			
			int nextX, nextY;
			//duyệt 4 hàng xóm của currPoint
			for (int i = 0; i < moveX.length; i++) {
				nextX = currX + moveX[i];
				nextY = currY + moveY[i];
				
				if(isSafePosition(nextX, nextY)) {
					q.enQueue(new Point(nextX, nextY));
					mark[nextX][nextY] = mark[currX][currY] + 1;
				}
			}
			
		}
		
		return -1;
	}

	public static void main(String[] args) throws FileNotFoundException {
		Solution s = new Solution();
		System.setIn(new FileInputStream(System.getProperty("user.dir") + "/princess.txt"));
		s.sc = new Scanner(System.in);
		s.T = s.sc.nextInt();
		for (int tc = 1; tc <= s.T; tc++) {
			s.input();
			//System.out.println("tc = " + tc + ", n = " + s.n);
			s.reset();
			int fromStartToPrincess = s.princess(1, 1);
			if(fromStartToPrincess == -1) {
				System.out.println("-1");
				continue;
			}
			
			s.reset();
			int fromEndToPrincess = s.princess(s.n, s.n);
			if(fromEndToPrincess == -1) {
				System.out.println("-1");
				continue;
			}
			
			System.out.println(fromStartToPrincess + fromEndToPrincess);
		}
	}
	
	/*
	 * rear: vị trí con trỏ chỉ tới phần tử cuối cùng của queue
	 * front: vị trí con trỏ chỉ tới TRƯỚC phần tử đầu tiên của queue
	 * ban đầu queue rỗng thì front = rear = -1;
	 * giả sử thêm 1 phần tử A vào queue, thì rear = 0 và front = -1.
	 * thêm 1 phần tử khác B vào queue, thì rear = 1 và front = -1.
	 * Khi lấy hết phần tử ra thì ta sẽ gán lại front = rear = -1 
	 */
	class Queue<T> {
		private int front, rear;
		private T arr[];
		
		@SuppressWarnings("unchecked")
		public Queue(int size) {
			arr = (T[]) new Object[size];
			front = rear = -1;
		}
		
		public boolean isEmpty() {
			return front==-1 && rear==-1;
		}
		
		/**
		 * Nếu rear trỏ tới phần tử cuối cùng của mảng arr
		 * thì queue đã full!
		 * @return true nếu queue đã full
		 */
		public boolean isFull() {
			return rear == arr.length - 1;
		}
		
		public int size() {
			return rear - front;
		}
		
		/**
		 * Push something into queue (push from rear)
		 */
		public boolean enQueue(T value) {
			if(isFull()) {
				return false;
			}
			
			rear++;
			arr[rear] = value;
			return true;
		}
		
		public T deQueue() {
			if(isEmpty()) {
				//System.out.println("Queue is empty!");
				return null;
			}

			front++;
			T value = arr[front];
			
			//Khi lấy hết các phần tử rồi thì front = rear, lúc này
			//ta nên cho 2 con trỏ này về vị trí đầu tiên của mảng arr
			if(front == rear) {
				front = rear = -1;
			}
			return value;
		}
		
		public void printQueue() {
			System.out.println("Printing queue, size = " + this.size());
			for (int i = front+1; i <= rear; i++) {
				System.out.print(arr[i] + " ");
			}
			System.out.println();
		}
		
		public void destroy() {
			front = rear = -1;
		}
	}
	
	static class Point {
		int x,y;

		public Point(int x, int y) {
			this.x = x;
			this.y = y;
		}
		
		@Override
		public String toString() {
			return "(" + x + ", " + y + ")";
		}
	}
}