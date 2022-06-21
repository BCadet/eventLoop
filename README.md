# eventLoop
Basic eventLoop in C

## Depedencies

This repository depends on [generic-linked-list](https://github.com/BCadet/generic-linked-list).
Checkout the submodule with the command `git submodule update --init` before building this project.

## Declaration

```
struct eventLoop event_loop;
```
## initialization

```
eventLoop_init(&event_loop);

struct event_binding binding;

//declare a binding between the action and the event 0
struct event_binding binding;
binding.action.command = my_command;
binding.action.args = my_args;
binding.eventMatchMask = (1 << 0);
binding.eventMatchPolicy = matchPolicyOR;

// add the binding to the eventLoop
eventLoop_add_event_bindings(&event_loop, binding);
```

## post action

```
struct action my_action;
my_action.command = my_command;
my_action.arg = my_arg;
eventLoop_post_action(&event_loop, &my_action);
```

## Loop execution

```
while (true)
{
    eventLoop_loop(&event_loop);
}
```
