import java.util.Scanner;

public class SSTF {

    public static void main(String [] args){
        Scanner input  = new Scanner(System.in);
        int [] queue = new int[100];
        int [] queue2 = new int[100];

        int head;
        int seek = 0;
        int qSize;
        int temp;
        float avg;

        System.out.println("SSTF Disk Scheduling");

        System.out.println("Enter queue size");
        qSize = Integer.parseInt(input.nextLine());

        System.out.println("Input Elements");
        for(int i=0; i<qSize;i++){
            queue[i] = Integer.parseInt(input.nextLine());
        }

        System.out.println("Enter initial head position");
        head = Integer.parseInt(input.nextLine());

        for(int i=0; i<qSize; i++){
            queue2[i] = Math.abs(head-queue[i]);
        }

        for(int i=0; i<qSize; i++){

            for(int j=i+1; j<qSize; j++){

                if(queue2[i] >queue2[j]){
                    temp = queue2[i];
                    queue2[i] = queue2[j];
                    queue2[j] = temp;

                    temp = queue[i];
                    queue[i] = queue[j];
                    queue[j] = temp;
                }

            }
        }

        for(int i=1; i<qSize; i++){
            seek = seek + Math.abs(head-queue[i]);
            head = queue[i];
        }

        System.out.println("Total seek time is " +seek);
        avg = seek/(float)qSize;
        System.out.println("Average seek time is " +avg);

    }
}
