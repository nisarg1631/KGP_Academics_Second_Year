import java.util.*;
import java.text.*;

public class ContactList {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Friend[] fl = new Friend[5];
		Scanner myObj = new Scanner(System.in);  // Create a Scanner object
		
		String myinput=myObj.nextLine();
		int i=0;
		//if(myinput.equals("sdf")) System.out.println(myinput);
		//ContactList cl = new ContactList();
		while(!myinput.equals("quit")) {
			fl[i] = CreateFriend(myObj);
			//fl[i].printobj();
			myinput=myObj.nextLine();
			i++;
		}
		int n=i;
		for(i=0;i<n;i++) {
			fl[i].printobj();
		}
		
	}
	
	static Friend CreateFriend(Scanner myObj) {
		//Scanner myObj = new Scanner(System.in);  // Create a Scanner object
		System.out.print("Enter the type: ");
		String mytype=myObj.nextLine();
		if(mytype.equals("personal")) return new PersonalFriend(myObj);
		if(mytype.equals("professional")) return new ProfessionalFriend(myObj);
		return null;
	}

}

class Friend {
	String name;
	String mobileno;
	String emailid;
	
	public Friend(Scanner myObj) {
		// TODO Auto-generated constructor stub
		//name=null;
		//mobileno=null;
		//emailid=null;
		//Scanner myObj = new Scanner(System.in);  // Create a Scanner object
		System.out.print("Enter the name: ");
		this.name=myObj.nextLine();
		System.out.print("Enter the mobileno: ");
		this.mobileno=myObj.nextLine();
		System.out.print("Enter the eamilid: ");
		this.emailid=myObj.nextLine();
	}
	void printobj() {
		System.out.println("Name: "+name);
		System.out.println("Mobile no: "+mobileno);
		System.out.println("Email: "+emailid);
	}
}

class PersonalFriend extends Friend {
	String birthday;
	
	public PersonalFriend(Scanner myObj) {
		// TODO Auto-generated constructor stub
		super(myObj);
		//birthday = new Date();
		System.out.print("Enter the Birthday: ");
		this.birthday=myObj.nextLine();
	}
	void printobj() {
		super.printobj();
		System.out.println("Birthday: "+birthday);
	}
	
}


class ProfessionalFriend extends Friend {
	String interests;
	
	public ProfessionalFriend(Scanner myObj) {
		// TODO Auto-generated constructor stub
		super(myObj);
		//birthday = new Date();
		System.out.print("Enter the Common Interests: ");
		this.interests=myObj.nextLine();
	}
	void printobj() {
		super.printobj();
		System.out.println("Common Interests: "+interests);
	}
	
}

