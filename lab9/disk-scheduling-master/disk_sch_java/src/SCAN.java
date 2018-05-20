/*
    SCAN - Disk Scheduling Algorithm (Elevator)

    scans down towards the nearest end and then when it hits the bottom,
    it scans up servicing the requests that it didn't get going down.
    If a request comes in after it has been scanned it will not be serviced
    until the process comes back down or moves back up.

 */

import java.util.Arrays;
import java.util.Scanner;

public class SCAN {
    public static void main(String [] args){
        Scanner input = new Scanner(System.in);
        int sum =0;
        int head;
        int [] queue;
        int max;
        int dloc = 0;  //location of disk(head) in arr

        System.out.println("Input no of disk locations");
        int qSize = Integer.parseInt(input.nextLine());

        queue = new int[qSize+1];
        System.out.println("Enter head position");
        head = Integer.parseInt(input.nextLine());

        System.out.println("Input elements in disk queue");
        for(int i=0; i<qSize; i++){
            queue[i] = Integer.parseInt(input.nextLine());
        }

        queue[qSize] = head;
        qSize++;

        //sort disk locations queue
        Arrays.sort(queue);

        max = queue[qSize-1];

        for(int i = 0; i<qSize; i++){
            if(head == queue[i]){
                dloc = i;
                break;
            }
        }

        for(int i = dloc; i>=0; i--){
            System.out.print(queue[i] + "-->");
        }

        System.out.print("0-->");

        for(int i=dloc+1; i<qSize; i++){
            System.out.print(queue[i] + "-->");
        }

        System.out.println();

        sum=head+max;
        System.out.println(" Movement of total cylinders " + sum);

    }

}
