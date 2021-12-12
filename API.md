# State

### Game
- objects: Object[]

### Object
- uuid: uint
- components: Component[]

### Component
- type: ComponentType
- data: ...

### ComponentType - enum
- transform
- inventory_owner
- collectable
- crafting_table

### TransformComponent
- positionX: float
- positionY: float
- orientation: float



# ClientMessage
- type: ClientMessageType
- data: ...

## ClientMessageType - enum
- player_movement
- object_interaction

### PlayerMovement
- playerUuid: uint
- position: TransformComponent

### ObjectInteraction
- uuid: uint
- type: InteractionType

### InteractionType - enum
- object pick



# ServerMessage
- type - ServerMessageType
- data: ...

## ServerMessageType - enum
- object_creation
- object_deletion

## ObjectCreation
- object: Object

## ObjectDeletion
- object_uuid: uint