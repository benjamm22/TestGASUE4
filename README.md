# TestGASUE4 - made in UE4.25

 UE4 Gameplay Ability System -- with custom MMORPG-Style character movement
 
 Designed with intent for multiplayer development
 
 **There are a lot of large comments as this was my first attempt at creating a project that uses the GAS and has multiplayer functionality**
 
 -------------------------------------------------------------------------------------------------------------------------------------
 ### Gameplay Ability System (GAS):
 
 GAS -- https://github.com/Pantong51/GASContent/blob/master/README.md\
 
 The GAS a very powerful tool designed by Epic that's used in Fortnite (and was going to be used in Paragon). The system was designed with intention for use in multiplayer (not required though). In a general sense, Gameplay Abilities cause Gameplay Effects. Those Gameplay Effects then cause changes to Attributes. It has a steep learning curve... again this is why I have so many large comments in my code.
 
 Dan's GAS example (**STRONG REFERENCE**... copy pasted a lot of info from here as comments to remember important info) -- https://github.com/tranek/GASDocumentation
 
 *^ this reference provides a lot of boilerplate code and I used a lot of it myself... most of the boilerplate code is creating and attaching the GAS components such as the AbilitySystemComponent and AttributeSet*
 
 -------------------------------------------------------------------------------------------------------------------------------------
 
 ### Player Controls:
 
 Forward movement: W & A **OR** both mouse buttons simultaneous
 
 Strafe: Q & E
 
 Rotate in place: A & D
 
 Control Camera: hold left click and drag
 
 Zoom Camera: mouse wheel
 
 *See the TGCharacterExample in Character/Heroes*
 
 -------------------------------------------------------------------------------------------------------------------------------------
 ## GAS Usage:
 
 Currently, source has 3 attributes -> MoveSpeed which is used to override our Character Movement Component
 others are WIP
 
 Targeting is WIP
