# Airconditioner
Undergraduate Software Engineering Course Project

Group project for software engineering course, built a temperature control system. There are four rooms, each room has an airconditioner. One central controller works as server. Users in each room can adjust the temperature and wind speed according to their need, they can see their current fee and the status of airconditioner. The centrol controller will monitor the conditions for each room and compute fees for each of them respectively, according to the energy cost. All the statistical things such as start/shut down times, the wind speed, the temperatures are all recorded. Because the central controller can only handle three machines, we designed a schedule algorithm so that when the fourth request comes, the controller will schedule the airconditioners according to their priorities. Load balancing is used to ensure each of the three rooms can be adjusted in time.

More details please see the requirement documents and the code.
