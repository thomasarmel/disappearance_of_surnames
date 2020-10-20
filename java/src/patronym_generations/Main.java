package patronym_generations;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class Main {
	/**
	 * Params
	 */
	final static int nbPersons=1000, nbPatronyms=200, nbGenerationsMax=5000;
	
	static List<Couple> generateCouples(List<Person> persons) {
		List<Couple> listCouples=new ArrayList<>();
		List<Integer> isUsed=new LinkedList<>();
		maleLoop:
		for(int i=0; i<persons.size(); i++) {
			if(persons.get(i).getMale()) {
				for(int j=i+1; j<persons.size(); j++) {
					if(!persons.get(j).getMale() && !isUsed.contains(j)) {
						isUsed.add(j);
						listCouples.add(new Couple(persons.get(i), persons.get(j)));
						continue maleLoop;
					}
				}
			}
		}
		return listCouples;
	}
	
	static List<String> getAllPatronyms(List<Person> persons) {
		List<String> listPat=new ArrayList<>();
		for(Person p : persons) {
			if(!listPat.contains(p.getPatronym())) {
				listPat.add(p.getPatronym());
			}
		}
		return listPat;
	}
	
	public static void main(String[] args) throws Exception {
		if(nbPersons<nbPatronyms) {
			System.err.println("Error: too many patronyms");
			System.exit(-1);
		}
		String[] patronyms=new String[nbPatronyms];
		Scanner sc=new Scanner(new File("patronyms.txt"));
		for(int i=0; i<nbPatronyms; i++) {
			if(!sc.hasNextLine()) {
				System.err.println("Error: file is too short");
				System.exit(-2);
			}
			String l=sc.nextLine();
			patronyms[i]=l.replaceAll("\\r|\\n", "");
		}
		sc.close();
		List<Person> listPersons=new ArrayList<Person>();
		int personsWithSamePatronym=nbPersons/nbPatronyms;
		Random rand=new Random();
		for(int i=0; i<nbPersons; i++) {
			listPersons.add(new Person(patronyms[i/personsWithSamePatronym], rand.nextInt(2)==0));
		}
		int totalPatronyms=getAllPatronyms(listPersons).size();
		System.out.println("Generation 0: " + totalPatronyms + " patronyms");
		for(int generation=0; generation<nbGenerationsMax && totalPatronyms>1; generation++) {
			Collections.shuffle(listPersons);
			List<Couple> listCouples=generateCouples(listPersons);
			int missingChildren=nbPersons-(listCouples.size()*2);
			for(int i=0; i<missingChildren; i++) {
				Couple c=listCouples.get(i%listCouples.size());
				c.setChildrenPerCouple(c.getChildrenPerCouple()+1);
			}

			listPersons=new ArrayList<Person>();
			listPersons.addAll(new ArrayList<Person>());
			for(Couple c : listCouples) {
				listPersons.addAll(c.makeChildren());
			}
			totalPatronyms=getAllPatronyms(listPersons).size();
			System.out.println("Generation " + (generation+1) + ": " + totalPatronyms + " patronyms");
		}
	}
}
