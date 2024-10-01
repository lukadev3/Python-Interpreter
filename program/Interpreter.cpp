#include <iostream>
#include "Interpreter.h"

Interpreter::Interpreter() : s("") {}  // Implementacija konstruktora

//substr(int a, int b) podstring od a duzine b
//find(string) pronalazi podstring u stringu
//npos je rezultat find, ako je -1 ne postoji podstring, u suprotnom vraca prvo indeks prvog pojavljivanja pocetka stringa 

void Interpreter::run() {
    std::string code;

    std::cout << "Enter Python code (for end of program, enter 'exit'):\n";

    while (true) {
		std::cout << ">>> ";
        std::getline(std::cin, code);

        if (code == "exit") {
            break;
        }
        std::istringstream iss(code);
        std::string command;
        iss >> command;
        
        if (code.find("=") != std::string::npos && ((code[code.find("=")+1] == '"' && code[code.size()-1] == '"')
												|| (code[code.find("=")+1] == '\'' && code[code.size()-1] == '\'')
												|| (code[code.find("=")+2] == '"' && code[code.size()-1] == '"')
												|| (code[code.find("=")+2] == '\'' && code[code.size()-1] == '\''))) { //dodela string promenljivoj
            std::string varName, varValue;
            std::size_t pos = code.find(" = ");
            if (pos != std::string::npos) {
                varName = code.substr(0, code.find("=")-1);
                if(lists.find(varName) != lists.end())
					variables.erase(varName);
				if(tuples.find(varName) != tuples.end())
					tuples.erase(varName);
                varValue = code.substr(pos + 3);
                varValue.pop_back();
                varValue.erase(0,1);
                variables[varName] = varValue; //uklanja "" sa pocetka i kraja i postavlja '' i tako dodeljuje vrednost pormenljivoj
            }else if(pos == std::string::npos){
				std::size_t pos = code.find("=");
				if (pos != std::string::npos) 
				{	
					varName = code.substr(0, code.find("="));
					if(lists.find(varName) != lists.end())
						variables.erase(varName);
					varValue = code.substr(pos + 1);
					varValue.pop_back();
					varValue.erase(0,1);
					variables[varName] = varValue;
				}
				else {
                std::cout << "Neispravna naredba za definisanje promenljive!" << std::endl;
            }
		}
        } else if (code.substr(0, 6) == "print(" && code[code.size()-1]==')') { //trazi print
            std::string varName = code.substr(6);
            varName.pop_back();
            if (variables.find(varName) != variables.end()) { //ako je string u pitanju 
                std::string varValue = variables[varName];
                s = Stringovi(varValue);
                std::cout << s.get() << std::endl;
            } else if((code[code.size()-2] == '\'' && code[code.find("(")+1] == '\'') || (code[code.size()-2] == '"' && code[code.find("(")+1]=='"')){
				//ovo je slucaj da se izmedju printa nalazi string (print("jabuka"))
				varName = code.substr(7);
				varName.pop_back();
				varName.pop_back();
                std::cout << varName << std::endl;
            }
            else if(lists.find(varName) != lists.end()){ //ako je lista
				Lista& list = lists[varName];
                list.print();
            }
            else if(tuples.find(varName) != tuples.end()){ //ako je torka
				Torka& torka = tuples[varName];
				torka.print();
				
            }else
				std::cout<<"Greska"<<std::endl;
        } else if (code.substr(code.find(".")+1) == "upper()") { //trazi se upper koji mala slova pretvara u velika
            std::string varName = code.substr(0,code.find("."));
            if (variables.find(varName) != variables.end()) { //ispituje se da li promenljiva postoji
                std::string varValue = variables[varName];
                s = Stringovi(varValue); //uzima se vrednost promenljive i salje konstruktoru za klasu Stringovi
                s.upper();
                std::cout << s.get() << std::endl;
            } else {
                std::cout << "Promenljiva '" << varName << "' nije definisana!" << std::endl;
            }
        } else if (code.substr(code.find(".")+1) == "lower()") { //trazi se lower koji velika slova pretvara u mala
            std::string varName = code.substr(0,code.find("."));
            if (variables.find(varName) != variables.end()) { //proverava da li postoji promenljiva
                std::string varValue = variables[varName];
                s = Stringovi(varValue); 
                s.lower();
                std::cout << s.get()  << std::endl;
            } else {
                std::cout << "Promenljiva '" << varName << "' nije definisana!" << std::endl;
            }
        } else if (code.substr(code.find(".")+1) == "strip()") { //trazi se strip koji uklanja razmake
            std::string varName = code.substr(0,code.find("."));
            if (variables.find(varName) != variables.end()) { //ispituje da li postoji promenljiva
                std::string varValue = variables[varName];
                s = Stringovi(varValue);
                s.strip();
                std::cout << s.get() << std::endl;
            } else {
                std::cout << "Promenljiva '" << varName << "' nije definisana!" << std::endl;
            }
        } else if(code.find("+") != std::string::npos){ //trazi se plus koji spaja stringove liste i torke
		
				std::string varName1, varName2, varValue1;
				std::size_t pos = code.find(" + "); //ovo je slucaj da linija izgleda a + b
				if(pos != std::string::npos){
					
					varName1 = code.substr(0,code.find("+")-1);
					varName2 = code.substr(code.find("+")+2);
					if(variables.find(varName1) != variables.end() && variables.find(varName2) != variables.end()){ //ispituje se da li su obe
													//promenljive stringovi
						varValue1 = variables[varName1];
						Stringovi s1(varValue1);
						Stringovi s2(variables[varName2]);
						Stringovi s3(s1+s2); //prepisan operator +
						std::cout << s3.get() << std::endl;
					}
					else if(lists.find(varName1) != lists.end() && lists.find(varName2) != lists.end()){ //ispituje se da li su promenljive liste
					
						Lista& list1 = lists[varName1];
						Lista& list2 = lists[varName2];
						Lista l = list1+list2;
						l.print();
					}
					else if(tuples.find(varName1) != tuples.end() && tuples.find(varName2) != tuples.end()){ //ispituje da li su promenljive torke
						Torka& t1 = tuples[varName1];
						Torka& t2 = tuples[varName2];
						Torka t3 = t1+t2;
						t3.print();
					}else
						std::cout<<"Ne postoji promenljiva"<<std::endl;
					
				}else if(pos == std::string::npos)
				{
					pos=code.find("+"); //ovo je slucaj da linija izgleda a+b
					if(pos != std::string::npos)
					{
						//ovaj deo koda je isti kao u prethodnom slucaju
						varName1 = code.substr(0,code.find("+"));
						varName2 = code.substr(code.find("+")+1);
						if(variables.find(varName1) != variables.end() && variables.find(varName2) != variables.end()){ 
							varValue1 = variables[varName1];
							Stringovi s1(varValue1);
							Stringovi s2(variables[varName2]);
							Stringovi s3(s1+s2);
							std::cout << s3.get() << std::endl;
						}
						else if(lists.find(varName1) != lists.end() && lists.find(varName2) != lists.end()){
					
							Lista& list1 = lists[varName1];
							Lista& list2 = lists[varName2];
							Lista l = list1+list2;
							l.print();
						}
						else if(tuples.find(varName1) != tuples.end() && tuples.find(varName2) != tuples.end()){
							Torka& t1 = tuples[varName1];
							Torka& t2 = tuples[varName2];
							Torka t3 = t1+t2;
							t3.print();
						}
						else
							std::cout<<"Ne postoji promenljiva"<<std::endl;
					}
					else {
					std::cout << "Neispravna naredba za definisanje promenljive!" << std::endl;
					}
					
				}
		
		} else if(code.find("*") != std::string::npos){ //trazi se * koji mnozi stringove liste i torke brojem
		
			std::string varName1,varValue1,varName2;
			int n;
			std::size_t pos = code.find(" * "); //ovo je slucaj kada je linija a * 2
			if(pos != std::string::npos){
				
				
				//isti kod kao kod plusa
				varName1 = code.substr(0,code.find("*")-1);
				varName2 = code.substr(code.find("*")+2);
				n=stoi(varName2);
				if(variables.find(varName1) != variables.end()){ 
					
					varValue1 = variables[varName1];
					Stringovi s1(varValue1);
					Stringovi s3(s1*n);
					std::cout << s3.get() << std::endl;
				}
				else if(lists.find(varName1) != lists.end()){
					
					Lista& list1 = lists[varName1];
					Lista l = list1*n;
					l.print();
				}
				else if(tuples.find(varName1) != tuples.end()){
					Torka& t1 = tuples[varName1];
					Torka t = t1*n;
					t.print();
				}else
					std::cout<<"Ne postoji promenljiva"<<std::endl;
				
			}else if(pos == std::string::npos)
			{
				pos=code.find("*");
				if(pos != std::string::npos)  //ovo je slucaj kada je linija a*2
				{
					
					//isti kod kao kod plusa
					varName1 = code.substr(0,code.find("*"));
					varName2 = code.substr(code.find("*")+1);
					n=stoi(varName2);
					if(variables.find(varName1) != variables.end()){ 
					
						varValue1 = variables[varName1];
						Stringovi s1(varValue1);
						Stringovi s3(s1*n);
						std::cout << s3.get() << std::endl;
					}
					else if(lists.find(varName1) != lists.end()){
					
						Lista& list1 = lists[varName1];
						Lista l = list1*n;
						l.print();
					}else if(tuples.find(varName1) != tuples.end()){
						Torka& t1 = tuples[varName1];
						Torka t = t1*n;
						t.print();
					}
					else
						std::cout<<"Ne postoji promenljiva"<<std::endl;	
				}
				else {
				std::cout << "Neispravna naredba za definisanje promenljive!" << std::endl;
				}
				
			}
		}else if(code.substr(0,4)=="len(" && code[code.size()-1]==')'){ //trazi se len koji odredjuje duzinu stringova torki i listi
			
			std::string varName;
			if((code[code.size()-2] == '\'' && code[code.find("(")+1] == '\'') || (code[code.size()-2] == '"' && code[code.find("(")+1]=='"')){
				//slucaj kada je izmedju zagrada string (len("jabuka"))
				varName = code.substr(code.find("(")+2);
				varName.pop_back();
				varName.pop_back();
				std::cout << varName.length() << std::endl;
				
			}
			else if((code[code.size()-2] == '\'' && code[code.find("(")+1] != '\'') || (code[code.size()-2] == '"' && code[code.find("(")+1]=='"')
			        || (code[code.find("(")+1] == '\'' && code[code.size()-2] != '\'' ) || (code[code.find("(")+1]=='"' && code[code.size()-2] != '"' )){
				std::cout << "Greska pri unosu" << std::endl;
			}
			else {
				//slucaj kada je izmedju zagrada promenljiva
				varName = code.substr(code.find("(")+1);
				varName.pop_back();
				if(variables.find(varName) != variables.end())  //ako je string
					std::cout << variables[varName].length() << std::endl;
				else {
					if(lists.find(varName) != lists.end()) { //ako je lista
						Lista& list = lists[varName];
						std::cout<<list.size()<<std::endl;
					}
					else if(tuples.find(varName) != tuples.end()){ //ako je torka
						Torka& torka = tuples[varName];
						std::cout<<torka.size()<<std::endl;
					}else
						std::cout<<"Greska"<<std::endl;
				}
			}
				
		}else if(code.find("replace(") != std::string::npos && code[code.size()-1]==')'){ //ttrazi se replace koji menja patern u stringu sa drugim
																								//stringom
			
			std::string varName1, varName2, varValue;
			if((code[code.size()-2] == '\'' && (code[code.find(",")+1] == '\'' || code[code.find(", ")+1] == '\''))
			  || (code[code.size()-2] == '"' && (code[code.find(",")+1] == '"' || code[code.find(", ")+1] == '"'))
			  || (code[code.find("(")+1] == '\'' && (code[code.find(",")-1] == '\'' || code[code.find(" ,")-1] == '\''))
			  || (code[code.find("(")+1] == '"' && (code[code.find(",")-1] == '"' || code[code.find(" ,")-1] == '"'))){ 
				  //ispituje se da li je validan unos string.replace("a", "b") a mogu se koristiti i ''
				
				
				varName1 = code.substr(code.find("(")+2,code.find(",")-(code.find("(")+2)-1); //ono sta se menja
				varName2 = code.substr(0,code.find("."));
				if(code.find(", ") != std::string::npos)
					varValue = code.substr(code.find(", ")+3, code.find(")") - (code.find(", ")+3)-1); //zamena
				else
					varValue = code.substr(code.find(",")+2, code.find(")") - (code.find(",")+2)-1); //zamena
																		
				s = Stringovi(variables[varName2]);
				s.replace(varName1, varValue);
				variables[varName2]= s.get();
				
			}
		}else if(code.find("count(") != std::string::npos && code[code.size()-1]==')'){ //trazi se count koji broji pojave podstringa u stringu 
										//broji i clanove u listama i torkama
			
			std::string varName1, varName2, varValue;
			varName2 = code.substr(0,code.find("."));
			if(variables.find(varName2) != variables.end()){ //ako je string
				if((code[code.size()-2] == '\'' && code[code.find("(")+1] == '\'') || (code[code.size()-2] == '"' && code[code.find("(")+1]=='"')){
					
					varName1 = code.substr(code.find("(")+2);
					varName1.pop_back();
					varName1.pop_back();
					varValue = variables[varName2];
					s = Stringovi(varValue);
					std::cout << s.count(varName1) << std::endl;
					
				}
				else if((code[code.size()-2] == '\'' && code[code.find("(")+1] != '\'') || (code[code.size()-2] == '"' && code[code.find("(")+1]=='"')
						|| (code[code.find("(")+1] == '\'' && code[code.size()-2] != '\'' ) || (code[code.find("(")+1]=='"' && code[code.size()-2] != '"' )){
					std::cout << "Greska pri unosu" << std::endl;
				}
				else { //ako se broje promenljive
					int b=0;
					varName1 = code.substr(code.find("(")+1);
					varName1.pop_back();
					for(auto o:variables){
						if(variables[varName1]!="")
							b=1;}
					if(b==1)
					{
						varName2 = code.substr(0,code.find("."));
						varValue = variables[varName2];
						s = Stringovi(varValue);
						std::cout << s.count(variables[varName1]) << std::endl;
					}
					else std::cout << "Ne postoji promenljiva" << std::endl; 
				
				}
			}
			else if(lists.find(varName2) != lists.end()){ //ako je lista 
				Lista& list = lists[varName2];
                std::string element;
                element = code.substr(code.find("(")+1, code.find(")") - (code.find("(")+1));
                element[0]='\'';
                element[element.size()-1]='\'';
                int count = list.count(element);
                std::cout << count << std::endl;
			}
			else if(tuples.find(varName2) != tuples.end()){ //ako je torka
				Torka& torka = tuples[varName2];
				std::string element;
                element = code.substr(code.find("(")+1, code.find(")") - (code.find("(")+1));
                element[0]='\'';
                element[element.size()-1]='\'';
                int count = torka.count(element);
                std::cout << count << std::endl;
			}
			else std::cout << "Ne postoji promenljiva" << std::endl; 
		}else if ((code.find(" = [")!= std::string::npos || code.find("=[") != std::string::npos) && code[code.size()-1] == ']') { //kreiranje liste
            std::string listName;
            if(code.find(" = [") != std::string::npos)
				listName = code.substr(0,code.find(" = ["));
			else
				listName = code.substr(0,code.find("=["));
			if(variables.find(listName) != variables.end())
				variables.erase(listName);
			if(tuples.find(listName) != tuples.end())
				tuples.erase(listName);	
            std::string element,e;
            e = code.substr(code.find("[")+1, code.find("]") - (code.find("[")+1));
            std::stringstream ss(e);
            std::vector<std::string> elements;
            if(e.find(", ") != std::string::npos){
				while (std::getline(ss, element, ' ')) {
					if(element[element.size()-1] == ',')
						element.pop_back();
					element[0] = '\'';
					element[element.size()-1] = '\''; //na kraju elementa se stavljaju '' i tako se dodaje u listu
					elements.push_back(element);
				}
			}
			else{
				while (std::getline(ss, element, ',')) {
					element[0] = '\'';
					element[element.size()-1] = '\''; //na kraju elementa se stavljaju '' i tako se dodaje u listu
					elements.push_back(element);
				}
			}
		   
            add_list(listName, elements);
        } else if (code.find("append(") != std::string::npos && code[code.size()-1] == ')') { //trazi se append koji dodaje clan u listu
            std::string listName;
            listName = code.substr(0,code.find("."));

            if (lists.find(listName) != lists.end()) {
                Lista& list = lists[listName];
                std::string element;
                element = code.substr(code.find("(")+1, code.find(")") - (code.find("(")+1));
                element[0] = '\'';
				element[element.size()-1] = '\''; //na kraju elementa se stavljaju '' i tako se dodaje u listu
                list.append(element);
            } else {
                std::cout << "Lista '" << listName << "' nije definisana!" << std::endl;
            }
        } else if (code.find("extend(") != std::string::npos && code[code.size()-1] == ')') { //trazi se extend koji prosiruje listu sa listom u zagradi
            std::string listName;
            listName = code.substr(0,code.find("."));

            if (lists.find(listName) != lists.end()) {
                Lista& list = lists[listName];
                std::string otherListName;
				otherListName = code.substr(code.find("(")+1, code.find(")") - (code.find("(")+1)); //uzima se ime promenljive izmedju zagrada

                if (lists.find(otherListName) != lists.end()) {
                    const Lista& otherList = lists[otherListName];
                    list.extend(otherList);
                } else {
                    std::cout << "Lista '" << otherListName << "' nije definisana!" << std::endl;
                }
            } else {
                std::cout << "Lista '" << listName << "' nije definisana!" << std::endl;
            }
        } else if (code.find("insert(") != std::string::npos && code[code.size()-1] == ')') { //trazi se insert za dodavanje u listu
            std::string listName;
            listName = code.substr(0,code.find("."));

            if (lists.find(listName) != lists.end()) {
                Lista& list = lists[listName];
                int i;
                std::string index;
                std::string element;
                index = code.substr(code.find("(")+1, code.find(",") - code.find("("));
                i=stoi(index);
                if(code.find(", ") != std::string::npos)
					element = code.substr(code.find(",")+2, code.find(")") - (code.find(",")+2));
				else 
					element = code.substr(code.find(",")+1, code.find(")") - (code.find(",")+1));
				element[0] = '\'';
				element[element.size()-1] = '\'';
                list.insert(i, element);
            } else {
                std::cout << "Lista '" << listName << "' nije definisana!" << std::endl;
            }
        } else if (code.find("remove(") != std::string::npos && code[code.size()-1] == ')') { //trazi se kljucna rec remove koja uklanja 
																					//clan izmedju zagrada u listi
            std::string listName;
            listName = code.substr(0,code.find(".")); 

            if (lists.find(listName) != lists.end()) {
                Lista& list = lists[listName];
                std::string element;
                element = code.substr(code.find("(")+1, code.find(")") - (code.find("(")+1));
                element[0] = '\'';
				element[element.size()-1] = '\'';
                list.remove(element);
            } else {
                std::cout << "Lista '" << listName << "' nije definisana!" << std::endl;
            }
        } else if (code.find("index(") != std::string::npos && code[code.size()-1] == ')') { //trazi se kljucna rec index koja ispisuje indeks
																						     //clana izmedju zagrada
            std::string listName;
            listName = code.substr(0,code.find("."));

            if (lists.find(listName) != lists.end()) { //ispituje da li je izmedju zagrada lista
                Lista& list = lists[listName];
                std::string element;
                element = code.substr(code.find("(")+1, code.find(")") - (code.find("(")+1));
                element[0] = '\'';
				element[element.size()-1] = '\'';
                int index = list.index(element);
                if (index != -1) {
                    std::cout << index << std::endl;
                } else {
                    std::cout << "Element '" << element << "' nije pronađen u listi." << std::endl;
                }
            } else if(tuples.find(listName) != tuples.end()){ //ispituje da li je izmedju zagrada torka
                Torka& torka = tuples[listName];
                std::string element;
                element = code.substr(code.find("(")+1, code.find(")") - (code.find("(")+1));
                element[0] = '\'';
				element[element.size()-1] = '\'';
                int index = torka.index(element);
                if (index != -1) {
                    std::cout << index << std::endl;
                } else {
                    std::cout << "Element '" << element << "' nije pronađen u listi." << std::endl;
                }
            }
            else std::cout<<"Ne postoji promenljiva"<<std::endl;
        } else if (code.find("reverse(") != std::string::npos && code[code.size()-1] == ')') { //trazi se kljucna rec reverse koja obrce listu
            std::string listName;
			listName = code.substr(0,code.find(".")); //kupi ime liste do tacke

            if (lists.find(listName) != lists.end()) { //proverava da li lista postoji
                Lista& list = lists[listName];
                list.reverse(); //obrce listu
            } else {
                std::cout << "Lista '" << listName << "' nije definisana!" << std::endl; //ako ne postoji
            }
        } else if (code.find("sort(") != std::string::npos && code[code.size()-1] == ')') { //trazi se kljucna rec sort koja sortira listu
            std::string listName;
            listName = code.substr(0,code.find(".")); //kupi se ime liste do tacke

            if (lists.find(listName) != lists.end()) { //provera da li lista postoji
                Lista& list = lists[listName];
                list.sort(); //sortira se
            } else {
                std::cout << "Lista '" << listName << "' nije definisana!" << std::endl;
            }
        } else if (code.find("clear(") != std::string::npos && code[code.size()-1] == ')') { //trazi se kljucna rec clear koja brise sve clanove
																			//liste
            std::string listName;
            listName = code.substr(0,code.find(".")); //kupi se ime liste do tacke lista.clear()

            if (lists.find(listName) != lists.end()) { //proverava se da li lista postoji, ako postoji brisu se elementi
                Lista& list = lists[listName];
                list.clear();
            } else {
                std::cout << "Lista '" << listName << "' nije definisana!" << std::endl; //ako ne postoji 
            }
        }else if ((code.find(" = (")!= std::string::npos || code.find("=(") != std::string::npos) && code[code.size()-1] == ')'){ //ispituje
														//da li se sa terminala unosi torka, torka se unosi izmedju obicnih zagrada
			
			std::string tupleName;
			if(code.find(" = (") != std::string::npos)
				tupleName = code.substr(0,code.find(" = (")); //skuplja ima torke pre znaka jednakosti
			else
				tupleName = code.substr(0,code.find("=(")); //isto
			if(variables.find(tupleName) != variables.end())
				variables.erase(tupleName); //ako postoji string sa istim imenom, brise ga
			if(lists.find(tupleName) != lists.end())
				lists.erase(tupleName); //ako postoji lista sa istim imenom, brise je
			std::string element,e; 
			e = code.substr(code.find("(")+1, code.find(")") - (code.find("(")+1)); //uzima ceo string koji se nalazi izmedju zagrada
						//primer: torka = ("1", "2", "3"), uzece "1", "2", "3"
			std::stringstream ss(e);
			std::vector<std::string> elements;
			if(e.find(", ") != std::string::npos){
				while (std::getline(ss, element, ' ')) { //trazi zarez i skuplja liniju do pojave spejsa ako ga ima pri unosu elemenata
					if(element[element.size()-1] == ',')
						element.pop_back();
					element[0] = '\'';
					element[element.size()-1] = '\''; //postavlja jednostruke navodnike na pocetak i kraj clana
					elements.push_back(element); //dodaje clan u torku
				}
			}
			else{
				while (std::getline(ss, element, ',')) { //ovde skuplja red do pojave zareza, ako se pri unosu ne prave razmaci
					element[0] = '\'';
					element[element.size()-1] = '\'';
					elements.push_back(element); //isto kao prethodni if
				}
			}		
			add_tuple(tupleName, elements); //dodaje torku u niz torki a pre toga dodaje elemente u torku
		}else if(code.find("max(") != std::string::npos && code[code.size()-1] == ')') { //trazi kljucnu rec max koja pronalazi
																						 //maksimalnog clana torke
			std::string tupleName;
            tupleName = code.substr(code.find("(")+1, code.find(")") - (code.find("(")+1)); 
            Torka& t = tuples[tupleName];
            std::cout<<t.max()<<std::endl;
			
		
		}else if(code.find("min(") != std::string::npos && code[code.size()-1] == ')'){ //trazi kljucnu rec min koja pronalazi
																						//minimalnog clana torke
			
			std::string tupleName;
            tupleName = code.substr(code.find("(")+1, code.find(")") - (code.find("(")+1));
            Torka& t = tuples[tupleName];
            std::cout<<t.min()<<std::endl;
		
		}else if(code.find("sorted(") != std::string::npos && code[code.size()-1] == ')'){ //trzi kljucnu rec za ispisivanje sortirane torke
																						   //prvobitna torka se ne menja, samo se ispisuje
																						   //sortirana
			
			std::string tupleName;
            tupleName = code.substr(code.find("(")+1, code.find(")") - (code.find("(")+1)); //izvlaci ime torke koje se nalazi izmedju zagrada
																							//koriste se f-je iz biblioteke algorithm.h
            Torka& t = tuples[tupleName];
            t.sort();
		
		}else if(code.find("delete ") != std::string::npos){ //trazi kljucnu rec delete koja sluzi za brisanje torke
															 //kada se torka jednom izbrise ne moze se odstampati jer vise ne postoji
			
			std::string tupleName;
			tupleName = code.substr(code.find(" ")+1);
			tuples[tupleName].clear();
			tuples.erase(tupleName);
			
		}
		else if(countWords(code) == 1){ //ispituje se da li je u terminalu uneta samo jedna rec, ako jeste proverava se da li je to string
									    //lista ili torka, ako jeste, stampa  
			
			if(variables.find(code) != variables.end())
			{
			Stringovi s(variables[code]);
				std::cout<<s.get()<<std::endl;
			}else if(lists.find(code) != lists.end())
				lists[code].print();
			else if(tuples.find(code) != tuples.end())
				tuples[code].print();
			else std::cout<<"Nepoznata naredba"<<std::endl;
			
		}else{ 
			std::cout<<"Nepoznata naredba"<<std::endl;
		}
	}
}		

//funkcija dodaje listu u svoj niz listi i listi dodaje elemente tako sto se poziva eksplicitni konstruktor

void Interpreter::add_list(const std::string& listName, const std::vector<std::string>& elements) {
		lists[listName] = Lista(elements);
}


//funkcija dodaje torku u svoj niz torki i torki dodaje elemente tako sto se poziva eksplicitni konstruktor

void Interpreter::add_tuple(const std::string& tupleName, const std::vector<std::string>& elements) {
    Torka torka(elements);
    tuples[tupleName] = torka;
}

//broji koliko reci ima jedna linija sa terminala

int Interpreter::countWords(const std::string& line) {
    std::istringstream iss(line);
    int count = 0;
    std::string word;
    
    while (iss >> word) {
        count++;
    }
    
    return count;
}




