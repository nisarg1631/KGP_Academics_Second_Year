import java.util.*;
import java.util.concurrent.ScheduledExecutorService;

public class retest {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        node n1 = new node(1);
        node n2 = new node(2);
        node n3 = new node(3);
        node n4 = new node(4);
        node n5 = new node(5);
        node n6 = new node(6);

        n1.addleftnode(n2);
        n1.addrightnode(n3);
        n2.addleftnode(n4);
        n2.addrightnode(n5);
        n3.addleftnode(n6);

        inorder(n1);
//        DynamicArray s = new DynamicArray();
//        s.add(input);
//        s.add(input);
//        s.add(input);
//        s.add(input);
//        s.add(input);
//        s.print();
//        stack s = new stack();
//        s.push(input);
//        s.push(input);
//        s.push(input);
//        System.out.println(s.pop());
//        System.out.println(s.pop());
//        s.push(input);
//        System.out.println(s.pop());
//        System.out.println(s.pop());
    }

    //inorder store left
    //print curr
    //go right

    //

    static void inorder(node n){
        if(n == null)
            return;
        Stack<node> s = new Stack<>();
        s.push(n);
        while(!s.isEmpty()){
//            s.push(s.peek().left);
            node curr = s.pop();
            if(curr==null)
                continue;
            if(s.isEmpty() || s.peek() != curr.right){
                s.push(curr.right);
                s.push(curr);
                s.push(curr.left);
            }
            else{
                System.out.println(curr.val);
            }
        }
    }
}

//push -> 1
//q1 -> 1

//push -> 2
//transfer from q1 to q2
//q2 -> 1
//q1 -> 2
//transfer from q2 to q1
//q1 -> 1 2

//push -> 3
//q2 -> 1 2
// q1 -> 3


//class stack {
//    Queue<Integer> q1, q2;
//    public stack(){
//        q1 = new ArrayDeque<>(); //primary queue
//        q2 = new ArrayDeque<>(); //auxiliary queue used during push
//    }
//    public void push(Scanner input){
//        int elem = input.nextInt();
//        // push everything from q1 to q2
//        while (!q1.isEmpty()){
//            int temp = q1.remove();
//            q2.add(temp);
//        }
//        // push new element to q1
//        q1.add(elem);
//        // push everything from q2 to q1
//        while (!q2.isEmpty()){
//            int temp = q2.remove();
//            q1.add(temp);
//        }
//
//    }
//    public int pop(){
//        int removed = q1.remove();
//        return removed;
//    }
//}

//class DynamicArray{
//    int[] a;
//    int curr;
//    int capacity;
//
//    public DynamicArray(){
//        //set initial capacity to say 2
//        a = new int[2];
//        capacity = 2;
//        curr = 0;
//    }
//
//    public void add(Scanner input){
//        int elem = input.nextInt();
//        if(curr == capacity){
//            //allocate new space and transfer contents, new capacity double of previous
//            int[] aux = new int[capacity];
//            for(int i=0; i<capacity; i++)
//                aux[i]=a[i];
//            a = new  int[capacity*2];
//            capacity = capacity*2;
//            for(int i=0; i<curr; i++)
//                a[i]=aux[i];
//            a[curr]=elem;
//        }
//        else {
//           a[curr] = elem;
//        }
//        curr+=1;
//    }
//
//    public void print(){
//        for(int i=0; i<curr; i++)
//            System.out.println(a[i]);
//    }
//}

class node{
    int val;
    node left, right;
    public node(int n) {
        val = n;
        left = null;
        right = null;
    }
    public void addleftnode(node n){
        this.left = n;
    }
    public void addrightnode(node n){
        this.right = n;
    }
}

//class tree{
//    node root;
//    public tree(){
//        root = null;
//    }
//
//}