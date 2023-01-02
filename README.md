# Philosophers
### Introduction
- 스레드와 뮤텍스를 이용하여 만든 프로그램입니다.
### Rules
|                       |                                                                                                                                                                                                                   |
| --------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Allowed functions** | memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock |
- 한 명 이상의 철학자가 둥근 테이블에 앉아 다음과 같은 세 행동 중 하나를 취합니다 : 먹기, 생각하기, 잠자기
- 철학자가 밥을 먹는 도중에는, 생각하거나 잠을 자지 않습니다. 마찬가지로 잠자는 도중에는 밥을 먹거나 생각할 수 없으며, 생각하는 도중에는 밥을 먹거나 잠들 수 없습니다.
- 철학자들은 둥근 테이블에 앉아있으며, 가운데에는 아주 큰 스파게티 그릇이 놓여 있습니다.
- 탁자 위에는 몇 개의 포크가 올려져 있습니다.
- 스파게티는 포크 하나만으론 집거나 먹기가 어렵기 때문에, 철학자들은 반드시 양 손에 포크를 쥐고 (2개의 포크를 사용하여) 먹어야 합니다.
- 철학자는 절대로 굶고 있으면 안 됩니다.
- 모든 철학자는 먹어야 합니다.
- 철학자들은 서로와 대화할 수 없습니다.
- 각 철학자는 다른 철학자가 언제 죽는지 알아챌 수 없습니다.
- 철학자가 밥을 다 먹었으면, 포크를 내려놓고 잠자기 시작합니다.
- 철학자가 잠을 다 잤으면, 생각하기 시작합니다.
- 철학자가 한 명이라도 사망하면 시뮬레이션이 종료됩니다.
- 각 프로그램은 같은 옵션을 가져야 합니다 : 철학자의 수, 철학자의 수명, 밥을 먹는데 걸리는 시간, 잠자는 시간, [각 철학자가 최소한 밥을 먹어야 하는 횟수] (number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat])
  - 철학자의 수 (number_of_philosophers): 테이블에 앉아 있는 철학자의 수와 포크의 수
  - 철학자의 수명 (time_to_die): 밀리초 단위로, 철학자가 마지막으로 밥을 먹은 지 'time_to_die' 시간만큼이 지나거나, 프로그램 시작 후 'time_to_die' 시간만큼이 지나면 해당 철학자는 사망합니다.
  - 밥을 먹는데 걸리는 시간 (time_to_eat) : 밀리초 단위로, 철학자가 밥을 먹는 데 걸리는 시간입니다. 해당 시간동안, 철학자는 두 개의 포크를 소유하고 있어야 합니다.
  - 잠자는 시간 (time_to_sleep) : 밀리초 단위로, 잠을 자는 데 소모되는 시간입니다.
  - 각 철학자가 최소한 밥을 먹어야 하는 횟수 (number_of_times_each_philosopher_must_eat) : 해당 인자값은 선택사항입니다. 모든 철학자가 'number_of_times_each_philosopher_must_eat' 횟수만큼 밥을 먹었다면, 시뮬레이션이 종료됩니다. 해당 값이 명시되어 있지 않다면, 철학자가 한 명이라도 사망할 때까지 시뮬레이션은 계속됩니다.
- 각 철학자에게는 1부터 'number_of_philosophers' 만큼의 고유 번호가 부여됩니다.
- 철학자 1번은 철학자 'number_of_philosophers'번 옆에 앉습니다. 그 외에, N번 철학자는 N-1번 철학자와 N+1번 철학자 사이에 앉습니다.
- 철학자의 상태는 다음과 같은 형식으로 출력되어야 합니다. (X는 철학자의 고유 번호로 대체되어야 하며, timestamp_in_ms는 현재 타임스탬프가 밀리초 단위로 표시되어야 합니다.)
  - timestamp_in_ms X has taken a fork
  - timestamp_in_ms X is eating
  - timestamp_in_ms X is sleeping
  - timestamp_in_ms X is thinking
  - timestamp_in_ms X died
- 철학자의 상태는 다른 철학자들의 상태와 뒤엉키거나 섞인 상태로 출력되면 안 됩니다.
- 철학자의 사망 시점과 이를 출력하기 까지의 틈이 10ms 이상이 되면 안 됩니다.
- 다시 말하지만, 철학자들이 최대한 죽지 않도록 설계해야 합니다!
### Examples
    $> ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
### Development document