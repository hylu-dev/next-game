# UBISOFT NEXT 2024 | Programming

---

This is my submission for Ubisoft NEXT 2024. The topic for this year was to make a game that involves
the concept of "firing projectiles".

## Dark Star: Showdown

![startscreen](https://github.com/hylu-dev/NextGame/blob/master/Documentation/startscreen.png)

Welcome to Dark Star: Showdown. A 3D, turn based, strategy game that pits you 1v1 against another player amidst a dying star.

### Game Overview

![demo](https://github.com/hylu-dev/NextGame/blob/master/Documentation/demo.gif)

Meet Dark-52, a dwarf star rumored to be abundant with resources and scientific knowledge. In the pursuit of advancement, nations have sent legions of ships to the star only to meet their unexpected doom as the star begins dying lightyears ahead of schedule.

You and another player pilot the remaining ships from opposing nations. As death draws near, the two of you face off in a final showdown of triumph.

The game starts with both players on opposite sides of the star. The goal is to confront the other player
and shoot them down before the star implodes and kills everyone.

#### Turn-Based

Player's take turn making moves, being able to fly around and 3 bullets per. After each turn, those 3 bullets will be reloaded. Flying around costs fuel and will not normally replenish each turn so players must be careful not to run out of fuel early.

Both ships start rather weak, but they can destroy surrounding asteroids to gather a resource called **scrap**.
Spend **scrap** to upgrade and refurbish your ship to prepare for combat.

#### Star Pulses

As the game progresses, the star will weaken and occasionally pulse having a few effects

- Players will take a bit of damage but also have their fuel replenished
- The star will shrink and pull players and asteroids closer
- The positioning of asteroids and players will shift as well, disorienting the area.
- Pulses can be manually triggered by shooting the star

After enough pulses, players will be pulled so close that they will be forced to confront eachother. If that's not enough,
after too many pulses, the star will explode leading to both players losing in a draw.

### Controls

*Fly your ship*
- Forward/Back: W / S
- Turn Left/Right: A / D
- Pitch Up/Down: Space / Shift
- Fire Weapon: F
*Spend scrap to improve your ship*
- Upgrade Weapon: 1
- Upgrade Speed: 2
- Heal health: 3
- Replenish fuel: 4
