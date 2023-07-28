1. functia open_train_station aloca memorie pentru gara, iar mai apoi pentru fiecare peron

2. functia close_train_station dezaloca memoria alocata unei gari

3. Functia show_existing_trains afiseaza in fisierul f trenurile si vagoanele pentru fiecare peron din gara station

4. Functia arrive_train aloca pe peronul platform memorie pentru un tren cu puterea locomotive_power

5. Functia leave_train dezaloca memoria pentru peronul platform

6. Functia add_train_car adauga la finalul trenului aflat pe peronul platform un vagon cu greutatea weight (asta dac exista respectivul peron si daca se afla un tren acolo)

7. Functia contains verifica daca pe peronul platform se afla un tren ce are un vagon de greutat weight. Cu ajutorul unor apeluri ale acestei functii, dar si ale functiei deleteonce,
 functia remove_train_cars sterge prima aparitie din trenul de pe peronul platform al vagonului de greutate weight, atat timp cat respectivul tren contine un astfel de vagon

8. Functia length, calculeaza lungimea trenului (numarul de vagoane), in timp ce removee elimina vagonul aflat pe pozitia pos din trenul de pe peronul platform, si returneaza un pointer la acesta. 
Functia insert insereaza un vagon transmis ca parametru pe pozitia pos in trenul de pe peronul platform.
Cu ajutorul apelurilor acestor 3 functii, functia move_train_cars indeplineste cerinta

9. Functia find_express_train calculeaza viteza fiecarui tren aflat in gara, si afla viteza maxima. Returneaza peronul pe care se afla trenul cu viteza maxima

10. Functia find_overload_train calculeaza viteza fiecarui tren aflat in gara, si returneaza positia pe care se afla trenul cu viteza negativa(cel care nu poate pleca de pe loc)

11. Functia find_optimal_train calculeaza viteza fiecarui tren aflat in gara si returneaza peronul pe care se afla cel cu cea mai mare viteza nenegativa.

12. Functia find_heaviest_sequence_train calculeaza cea mai grea secventa de cars_no vagoane din fiecare tren din gara(asta daca trenul are lungimea minima cars_no), si pastreaza in cautat vagonul cu care incepe respectiva secventa.
 In final, este returnat peronul unde se alfa secventa maxima de lungime cars_no, iar start_car primeste vagonul cu care incepe acea secventa cautata

13. Functia order_train foloseste un algoritm de tip bubble sort, si inverseaza cele 2 vagoane vecine ce nu respecta ordinea in care se doreste ordonarea vagoanelor(NU face doar "schimb" de greutati)

14. Functia fix_overload_train gaseste trenul ce nu poate pleca de pe loc din gara, iar mai apoi gaseste fiecare vagon in lipsa caruia, el ar putea pleca din loc.
 Gaseste vagonul cu greutatea cea mai mica ce indeplineste aceasta conditie si in final il elimina prin apelul functiei deleteonce
