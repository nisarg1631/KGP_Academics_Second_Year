import java.util.*;
import java.util.stream.Collectors;

public class foo {
    public static void main(String[] args) {
        HashMap<String, StringBuilder> mymap = new HashMap<>();
        mymap.put("hello", new StringBuilder("hello"));
        mymap.put("how", new StringBuilder("how"));
        mymap.put("are", new StringBuilder("are"));
        StringBuilder[] cars = mymap.values().toArray(new StringBuilder[0]);
        for(StringBuilder s: cars)
            s.append(" edited");
        System.out.println(mymap);
    }
}

class sample{
    int id;
    String name;
    HashMap<Integer, sample> test2 = new HashMap<>();
    public sample(int id, String name){
        this.id=id;
        this.name=name;
    }
    public void edit(HashMap<Integer, sample> test){
        test.get(3).id++;
        test.get(4).name+="sumbitch";
        test2.put(11,test.get(1));
        test2.put(12,test.get(4));
    }
    public void edit2(){
        test2.get(11).id++;
        test2.get(12).name+=" yo bitch";
    }
}
