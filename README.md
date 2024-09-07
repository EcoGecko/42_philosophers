# Philosophers
##### graded **115/100**.
### **About**
This project introduces the concept of multithreading and multiprocessing to solve the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem). <br>
#### **Philosopher main routine**
All philosophers need to grab two forks to be able to eat, after they finish eating they let go of the forks and go to sleep. Any other moment they should be thinking. If one of the philosophers cannot eat for a specified amount of time it should die and the program stop.


### **Compilation/Execution**
Just cd into the desired dir, either philo for threading or philo_bonus for multiprocessing and run `make`, this will create an executable either `philo` or `philo_bonus` and run it as in the example:

```sh
$ ./philo <number_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_meals>
```
<number_of_philos> - Numbers of philosophers and also the number of forks.

<time_to_die> - If the time between two meals of a philosophers is greater than this parameter it dies (in miliseconds).

<time_to_eat> - Time a philosophers takes to eat. During this time it holds two forks (in miliseconds).

<time_to_sleep> - Time a philosopher will spend spleeping (in miliseconds).

<number_of_meals> - Optional parameter. Indicates the minimal amount of time a philosopher has to eat. When all philosophers eats at least this amount the simulation stops. If not specifies the simulation should only stop when one of the philosopher dies.
