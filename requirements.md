# Requirements

## measurement
- it should not be hard to measure performance
- it should not be hard to determing blame for poor performance

## speed
- actor and component management should not have too high an overhead

## memory
- memory use of actors and components should not be overly wasteful

## initialization
- it should not be bothersome to create actors
- it should not be hard to give actors' components initialization arguments

## manipulation
- manipulation of actors should not induce coupling to the actor types
  themselves, but only to specific components
- it should not be hard to get relevant data from an actor from one or
  more components
- it should not be difficult to call methods on other components

## release
- it should not be hard to signal/identify when an actor is dead
- actors should not be left allocated when they are no longer needed
- it should not be difficult to deallocate memory belonging to actors
- it should not be difficult to deallocate memory belonging to components

## safety
- it should not be too easy to have dangling pointers to actors
- it should not be too easy to have dangling pointers to components
- it should not be hard to specify and enforce interface contracts

## design
- it should not be hard to add new actor types
- it should not be difficult to add new components
- it should not be hard to change components to reflect changes in requirements

## documentation
- it should not be too hard to document the purpose and functioning of actors
- it should not be too hard to document the purpose and functioning of
  components
- it should not be too hard to document relationships between actors and
  components within a larger system
- it should not be too hard to partition actors and components based on
  function
- it should not be hard to specify and enforce dependencies between components
