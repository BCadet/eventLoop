# eventLoop
Basic eventLoop in C

## Declaration

```
struct eventLoop event_loop;
```
## initialization

```
eventLoop_init(&event_loop);
```

## post event

```
struct event my_event;
my_event.command = my_command;
my_event.arg = my_arg;
eventLoop_post_event(&event_loop, &my_event);
```

## Event execution

```
while (true)
{
    eventLoop_loop(&event_loop);
}
```
