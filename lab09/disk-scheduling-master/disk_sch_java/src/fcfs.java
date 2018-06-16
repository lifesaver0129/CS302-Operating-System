import java.util.Scanner;

public class fcfs {

    public static void main(String [] args){
        Scanner input = new Scanner(System.in);
        int seek = 0;
        int diff = 0;
        int head = 0;
        float avg;
        int[] queue;

        System.out.println("FCFS Disk Scheduling");

        System.out.println("Enter queue size");
        int qSize = Integer.parseInt(input.nextLine());

        queue = new int[qSize];

        System.out.println("Input Queue elements");
        for(int i=0; i<qSize; i++){
            queue[i] = Integer.parseInt(input.nextLine());
        }

        System.out.println("Enter initial head position");
        head  = Integer.parseInt(input.nextLine());

        queue[0] = head;

        for(int j=0; j<qSize-1; j++){
            diff = Math.abs(queue[j+1]-  queue[j]);
            seek += diff;
            System.out.println("Move " +queue[j] + " to " + queue[j+1] + " with seek " + diff);

        }

        System.out.println("Total Seek time is " + seek);
        avg = seek/(float)qSize;
        System.out.println("Average seek time is " +avg);

    }



}
