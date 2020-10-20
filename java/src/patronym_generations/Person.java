package patronym_generations;

public class Person {
	private String patronym;
	private boolean isMale=false;
	
	public Person(String p, boolean male) {
		patronym=p;
		isMale=male;
	}
	
	public String getPatronym() {
		return patronym;
	}
	
	public boolean getMale() {
		return isMale;
	}
	
	public String toString() {
		return (isMale ? "Mr " : "Ms ") + patronym;  
	}
}
