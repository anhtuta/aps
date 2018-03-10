/*
Point of Balance 2
There exist n magnetic materials in a gravity-free space. The center 
of each magnetic material is the location, i.e., the spatial coordinate 
(x,y,z). Coordinates y and z of n magnetic materials are the same, and 
only the coordinates of x are different. In other words, it is assumed 
the magnetic materials exist in a straight line. The location of the magnetic 
materials is never changed by any external force. Now, when an object is 
located in a random position in the straight in which n magnetic materials 
exist, gravitational force acts from each magnetic material. The gravitational 
force acting from a magnetic material on the object is obtained by the distance 
(d) between the magnetic material and the object and by the masses of the 
magnetic material and the object.

Formula for calculating the gravitational force acting from a magnetic 
material on the object:

F = G*m1*m2/(d*d), G is a positive constant.

Between the magnetic materials on the left and those on the right, the 
object moves in the direction of magnetic materials with bigger force. 
It is when that the two gravitational forces become the same, the object 
stops moving. Find the point where both forces become the same. When there 
are n magnetic materials, n-1 points of balance exist.


Point of balance: where both forces become the same: Pulling force of 
left magnetic materials = Pulling force of right magnetic materials


Note that errors of the coordinate values must be less than 10-9 (1e-9).

[Input]
A total of 10 test cases are given. For each test case, the number of magnetic 
materials N is written. In the next line, N x coordinate values, and N mass 
values are input sequentially. The number (N) of magnetic materials comes 
between 2 and 10 (2 ≤ N ≤ 10).

[Output]
For each test case, print “#C” in the first line with C being case number. 
Leave a blank space and print out x coordinate values of the points of 
balance in the same line. If the coordinate value has 10 or more digits 
after the decimal point, print only up to10 digits.

[Input/output example]
input:
2
1 2 1 1
2
1 2 1 1000
2
457 468 333 321
3
1 2 3 1 2 1
4
2 3 5 7 3 2 7 5
5
3 11 12 19 29 542 661 450 521 366	
6
42 75 88 94 113 144 669 551 355 344 294 155
7
62 86 279 323 363 516 579 810 749 736 297 136 107 52
8
10 34 64 73 93 97 101 122 466 463 441 373 315 292 225 83
10
9 14 38 39 48 73 179 190 207 302 560 497 640 722 437 259 449 470 709 520

output:
#1 1.5000000000 
#2 1.0306534300 
#3 462.5504629633 
#4 1.4060952085 2.5939047915 
#5 2.5328594461 3.7271944336 6.0999536409 
#6 6.3428568767 11.5477377494 15.9641592998 24.9267991616 
#7 57.8805685416 81.8651598883 91.0573691382 105.0835650492 133.2934094882 
#8 74.2211477711 190.6837563314 305.8269181687 348.3304429927 470.2694219294 555.4943093854 
#9 21.5171374463 47.9890597763 68.6536668433 82.9131954024 95.0052272762 99.1999097771 116.4978330953 
#10 11.5573600056 24.0238341338 38.4847676135 44.6137453708 64.7500445425 126.9908128982 184.3221650928 197.9760596292 266.0574653677 

*/
/*
Bài này hiểu như sau:
có n điểm từ thẳng hàng nhau như ở dưới (ký hiệu = dấu *) (n = 9)
	*    *    *     x    *     *     *     *     *     *
x là 1 điểm nào đó trên đường thẳng đó, khi đó 3 điểm từ bên trái
sẽ kéo x về phía chúng với 1 lực = f1, và 6 điểm từ bên phải
sẽ kéo x về phía chúng với 1 lực = f2. Ta cần tìm tọa độ của x
để f1 = f2 với sai só ko quá 10^-9
Chú ý rằng sẽ có 8 điểm x như vậy (8 điểm mà lực kéo bên trái = lực
kéo bên phải)
Mỗi điểm từ sẽ kéo x với 1 lực = F = G*m1*m2/(d*d),
m1, m2 là khối lượng của điểm từ và x. có thể cho G = m2 = 1, nghĩa là
chỉ quan tâm tới khối lượng của * và khoảng cách tới x

*/
package hello;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Solution {
	final double ERROR = 0.0000000001;
	final int NUM_OF_TESTCASES = 10;
	static int G = 1;
	static int m2 = 1;
	long T;
	int n;
	int []coor;		//tọa độ các điểm từ
	int []mass;		//trọng lượng của các điểm từ
	Scanner sc;
	
	public void input() {
		n = sc.nextInt();
		coor = new int[n+1];
		mass = new int[n+1];
		
		for (int i = 1; i <= n; i++) {
			coor[i] = sc.nextInt();
		}
		for (int i = 1; i <= n; i++) {
			mass[i] = sc.nextInt();
		}
	}
	
	/**
	 * Tính sự chênh lệch lực kéo giữa bên trái và bên phải,
	 * dựa vào hàm F = G*m1*m2/(d^2)
	 * @param x - tọa độ của điểm cần tính lực kéo
	 * @return - giá trị chênh lệch lực kéo
	 */
	public double totalForce(double x) {
		int i = 1;
		double leftForce = 0, rightForce = 0;
		double d;
		while(coor[i] <= x) {
			//System.out.println("\ti = " + i);
			d = x - coor[i];
			leftForce += G*mass[i]*m2/(d*d);
			i++;
		}
		
		while(i <= n && coor[i] >= x) {
			//System.out.println("\ti = " + i);
			d = coor[i] - x;
			rightForce += G*mass[i]*m2/(d*d);
			i++;
		}

		//System.out.println("x = " + x + ", totalForce = " + (leftForce - rightForce));
		return leftForce - rightForce;
	}
	
	/**
	 * Tìm tọa độ của điểm balance trong khoảng [lo, hi]
	 * @param lo
	 * @param hi
	 * @return tọa độ của điểm balance
	 */
	public double findBalance(float lo, float hi) {
		double low = lo, heigh = hi;
		double mid, force;
		while(heigh - low > ERROR) {
			mid = (heigh + low)/2;
			force = totalForce(mid);
			if(force == 0) {
				return mid;
			}
			if(force > 0) {
				low = mid;
			} else {
				heigh = mid;
			}
			//System.out.println("heigh = " + heigh + ", low = " + low + ", totalForce = " + totalForce(mid));
		}
		return heigh;
	}
	
	public static void main(String[] args) throws FileNotFoundException {
		Solution s = new Solution();
		
		System.setIn(new FileInputStream(System.getProperty("user.dir") + "/balance.txt"));
		s.sc = new Scanner(System.in);
		//s.T = s.sc.nextInt();
		s.T = s.NUM_OF_TESTCASES;
		for (int tc = 1; tc <= s.T; tc++) {
			s.input();
			System.out.print("#" + tc + " ");
			for (int i = 1; i <= s.n-1; i++) {
				System.out.printf("%.10f ", s.findBalance(s.coor[i], s.coor[i+1]));
			}
			System.out.println();
		}
	}
}

