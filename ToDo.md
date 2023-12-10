To do:
- To use Boost.asio to do the socket communication.
- IK: check the joint limits
- Complete the error_def file
- Add the header on all file, with project, descrption and all.

Bug da risolvere
- Comunicazione Tcp. Se la chiudo poi non riesco più a ri-attivarla.
- Unity rispedisce le coordinate ricevute come risposta invece di leggere le coordinate reali del robot.

Cinematica
1. movimento PTP con profilo di movimento a S (curva a 7 segmenti).
2. movimento lineare di sola traslazione (A, B e C constanti) con profilo di movimento a S (curva a 7 segmenti). Lontano da singolarità.
3. movimento lineare completo (rototraslazione) con profilo di movimento a S (curva a 7 segmenti). Lontano da singolarità.
4. movimento lineare completo (rototraslazione) con profilo di movimento Bezier. Lontano da singolarità.


Alla fine devo dare la scelta del tipo di traiettoria (profilo di movimento):
- Curva a S (curva a 7 segmenti).
- Bezier.
- Ottimizzato.

2023.12.10: Ho copiato la classe Pose e l'ho rinominata Trajectory. Lo scopo era quello di copiare il codice della funzione Line, che avevo già scritto, all'interno di questo progetto.
Devo completare questa classe con le funzioni necessarie per il calcolo delle traiettorie.
Nella funzione Line ho implementato la Curva a S, ma deve essere ancora finita. Devo per esempio analizzare i casi in cui alcune parti della curva a 7 segmenti si eliminano.