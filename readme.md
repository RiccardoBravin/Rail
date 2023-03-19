Railway management project performed for the Advanced Programming course in UniPD


Il lavoro è stato così diviso:
Elia: Railway, Timetable, SimulationE
Riccardo: Train, SimulationR
Angelo: Station, SimulationA, Cmake

Abbiamo iniziato dividendoci i .h di Railway, Timetable, Train, Station e poi ognuno ha iniziato con il rispettivo .cpp
Una volta ultimati Train e Station, Angelo ha iniziato a studiare l'utilizzo di cmake mentre Riccardo ed Elia hanno scritto .h e parte dello pseudocodice per Simulation
Mentre Elia ultimava Railway e Timetable, Riccardo ha scritto SimulationR.cpp e testato il suo corretto funzionamento
Una volta al termine delle loro parti Angelo ed Elia hanno ultimato Simulation con alcune funzioni in SimulationA e SimulationE
Durante tutto lo svolgimento dell'assegnamento siamo rimasti in stretto contatto per poter discutere su variazioni al codice già scritto e diverse idee implementative

Non essendoci interazioni tra le railway in un senso e nell'altro abbiamo diviso l'idea di railway rendendola unidirezionale. 
Ogni treno verrà simulato dall'orario di partenza dalla prima stazione e successivamente svolgerà le azioni indicate da simulation.
I metodi non sono esattamente efficienti in termini di prestazioni ma più comprensibili alla lettura considerato anche che treni e stazioni non sono numeri che possono tendere a +inf
