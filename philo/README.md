*This project has been created as part
of the 42 curriculum by jemonthi.*

# Description

Philosophers is a 42 project where you have one or more philosophers sit at a round table, each Philosophers need 2 forks to eat a bowl of spaghetti in the middle of the table, and they take turns to think, eat and sleep.
There is the same amount of philosophers and forks. If there is 1 philosopher, there is only 1 fork for example. 

You will have **5 arguments** or **6 arguments** : 

- argv[0] = your executable "philo".
- argv[1] = **number_of_philosophers**.
- argv[2] = **time_to_die** (in ms).
- argv[3] = **time_to_eat** (in ms).
- argv[4] = **time_to_sleep** (in ms).
- argv[5] = **number_of_time_each_philosophers_must_eat**

number_of_time_each_philosophers_must_eat is optional.

 Any state change of a philosopher must be formatted as follows:
- timestamp_in_ms X has taken a fork
- timestamp_in_ms X is eating
- timestamp_in_ms X is sleeping
- timestamp_in_ms X is thinking
- timestamp_in_ms X died  

Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.


- A displayed state message should not overlap with another message.

- A message announcing a philosopher’s death must be displayed within 10 ms of their actual death.
- Again, philosophers should avoid dying!

# Instructions

To compile all the files just run **make** at the root of the repository.

> make

It will create the executable "philo", to test it just type like the example below :

> ./philo 5 4000 200 200

It will create 5 philosophers that should be eating, sleeping and thinking without finishing for this example.

If you wanna test to put 6 args with a number_of_time_each_philosophers_must_eat : 

> ./philo 5 4000 200 200 10

Each philosophers will eat 10 meals before the simulation stops.

You can also check with a low number in time_to_die to see the simulation stops when a philosopher dies like below :

> ./philo 5 400 200 200 10

You can test with any number > 0 and <= INT_MAX, but remember, the higher your number is, the more time it will take to finish the simulation. I recommend you to use with low number and a max of 10000 if you don't wanna wait too long.

# Ressources

Here are some documentations i have read/watched during the project :

- https://man7.org/linux/man-pages/man2/gettimeofday.2.html
- https://youtu.be/mvZKu0DfFLQ?si=m0EfL-oNV_iRMda0
- https://www.ibm.com/docs/fr/aix/7.3.0?topic=programming-using-mutexes
- https://man7.org/linux/man-pages/man3/usleep.3.html
- https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3.html
- https://koor.fr/C/cthreads/Index.wp
- https://www.youtube.com/watch?v=VYPcmMo1sYk