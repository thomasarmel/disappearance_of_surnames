package patronym_generations;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Couple {
	private int childrenPerCouple=2;
	private Person[] members=new Person[2];
	private Random rand=new Random();
	
	public Couple(Person p1, Person p2) {
		if(p1.getMale()) {
			members[0]=p1;
			members[1]=p2;
		} else {
			members[1]=p1;
			members[0]=p2;
		}
	}
	
	public void setChildrenPerCouple(int n) {
		childrenPerCouple=n;
	}
	
	public int getChildrenPerCouple() {
		return childrenPerCouple;
	}
	
	public List<Person> makeChildren() {
		List<Person> listReturn=new ArrayList<>();
		for(int i=0; i<childrenPerCouple; i++) {
			listReturn.add(new Person(members[0].getPatronym(), rand.nextInt(2)==0));
		}
		return listReturn;
	}
	
	public String toString() {
		return "["+members[0]+", "+members[1]+"]";
	}
}
