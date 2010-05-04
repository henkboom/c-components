# Requirements

## performance
- performance measurement
- performance blame according to actors/components
- actor and component management shouldn't have too high an overhead
- memory use of actors and components shouldn't be overly wasteful

## game management
- extensible execution phases
- scene transitions

## actor initialization
- easy actor instantiation
- components initialization arguments in actor instantiation

## actor manipulation
- low coupling between actors by using components as interfaces
- getting information from an actor
- easily calling component methods
- components need access to their enclosing actor
- components need access to their enclosing game

## actor release
- signaling actor death
- finding out about actor death
- timely release of dead actors
- release of components belonging to dead actors

## safety
- there should be no dangling pointers to actors
- there should be no dangling pointers to components
- specification and enforcement of component interface contracts
- specification and enforcement of dependencies between components

## design
- easy addition of new actor types
- easy addition of new components
- easy modification of existing components

## documentation
- documentation of purpose and functioning of actors
- documentation of purpose and functioning of components
- documentation of actor-component relationships within a larger system
- flexible organization/categorization of actors and components
