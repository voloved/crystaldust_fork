# Todo and known bug list for CrystalDust:

## Known Bugs:
### General
* Occasional intense lag when returning from the nicknaming screen. (Could this be DN-related? Happens consistently in the grass patch just south of Goldenrod.)
* Camera should be locked when the OW Fly field move animation happens.
* Fishing encounter percentages are not accurate to Crystal.
* The GB Sounds table is not entirely filled out yet. Some songs that should have a GBS equivalent are not assigned.
* Learning a TM cuts off the bag message box when you press yes.
* Port FRLG Itemfinder field effects. The FRLG Itemfinder does **not** pick up regular items underfoot. In fact, if the player's on top of a hidden item, it'll show the arrows in their facing direction instead of printing any indication that they're right on top of it. Change this to mention that the player is on top of an item like in RSE when porting, since this is stupid.
* The `B_TRANSITION_WAVE` battle transition is broken and jumbles the transition. The other battle transitions are fine.

### Johto
* Azalea Town map name popup instantly dismisses in the outdoor town (Celebi event scripting mistake).
* If you change the station off of Oak's Pokémon Talk while it's in the middle of printing "POKéMON POKéMON\nPOKéMON CHANNEL", it'll clear the box when you change the channel but it'll print the rest of the string from where it left off. [Bug report with screenshot.](https://discord.com/channels/237788642238660610/789393113315409951/953906750988361788)
* The Rival is in Dragon's Den on the wrong days and before becoming Champion.

## Things that work, but need another pass or more testing for quality control:
* Gym Leader movesets need to be redone. Gyms 4-16 are using Crystal sets. Gyms 1-3 need another pass now that tutor moves are a thing (Bugsy should have Fury Cutter instead of Steel Wing).
* Elite Four and Champion movesets should be redone. They are currently using Crystal sets.
* Late Rival battles should probably have their movesets made custom, as they are laughable (Indigo Plateau Water Gun Feraligatr, for example).
* The Trainer Card needs to be checked when filled out. Also need to check all Trainer Cards (RS, E, FRLG, CD) displayed in the link rooms to make sure they are correct.
  * The Cianwood Photo Studio doesn't actually put images on the back of the trainer card.
* Bill might not be always calling to unlock Sevii after unlocking Mt. Silver. Need to check again.
* The Pokédex cursor indicator on Area/Cry/Size is too dim and needs a more drastic color change to be visible on OG GBA screens.
* New Johto tree tiles.
* The Bayleef OW sprite could use a quality control pass. It is in the Vermilion Pokémon Fan Club building.
* Morty's OW sprite side frames look bad and should probably be redone.
* Clair's OW sprite side frames look bad and should probably be redone.
* Need to check to make sure the Bug Catching Contest doesn't try to give you a mon when your party and boxes are full.
### Phone Calls
* All phone call-related text from trainers and Buena, both their OW NPC text and the phone call text themselves, need to be checked for placement in the textbox and textbox overflow. (OW NPC and phone call text for Joey, Wade, Liz, Ralph, Anthony, Todd, & Gina have been checked.)
* Script flow for registering a trainer in the OW needs to match Crystal. (Currently, only Joey, Wade, Liz, Ralph, Anthony, Todd, & Gina are done.)
  * **NOTE:** When a rematch is triggered in Crystal, there is no text after the battle. The script just ends.
* The timing system for calls acts like Emerald instead of Crystal. This essentially means you can guarantee calls immediately by soft-resetting. Need to port Crystal's logic for this.
* Check that gifts, swarms, sales, etc. get triggered correctly (Wade and Gina's gifts have been checked).
* Crystal has the initial roster as a rematch roster. The initial roster has to be beaten a second time to unlock the next roster up (at least for Youngster Joey). Should this be replicated?
* In Crystal, contacts are ordered by when the player acquired the number. In CD, they're in a fixed order (i.e. Bug Catcher Wade is always before Camper Todd).
#### (In progress, only Joey is accurate for now.)
* In Crystal, NPCs with a rematch queued can use their generic text in their calls instead of always calling to remind the player about the pending rematch.
* Phone calls are more complicated than randomly selecting generic text in Crystal. [See this Discord message](https://discord.com/channels/237788642238660610/789393113315409951/1181042716365312030). Should the generic texts stuff be refactored into just a regular script so that the Crystal phone scripts can be converted 1-to-1?
## Content within the current playable areas that is unfinished:
### General
* Lots of music is missing and instead plays placeholder tunes. Generally, unique songs past Sudowoodo are missing.
* Mom's obscure calls for random items after all of her listed items are bought are not implemented.
* The original Crystal IR Mystery Gift replacement is entirely unimplemented. Testers should not attempt to mix records at all.
* The Unown Dex is entirely unimplemented and absent.

### Johto
* Tin Tower's rooftop is using a placeholder map. Need a tileset for it.
* Bill and the GS Ball nurse should actually use and animate with the escalators. Currently, they just appear at the bottom.
* Mahogany's shop doesn't have its music change coded. Need to wait for music insertion.
* DJ Mary needs a unique OW sprite.
* Lance should use the Fly field move when flying away from the Lake of Rage. Currently, he teleports.
* The decorating menu in the player's room PC is not implemented. As a consequence, the player cannot decorate their room.
* The entire Celebi event is coded as it was in VC Crystal, but is not enabled.
  * Ilex Forest's trees don't wiggle when the Celebi event is underway. The art for the animation needs to be done.
* The Pokémon Communication Center in Goldenrod is not fully operational yet, but the fully-operational version of it is scripted and mapped. The trigger for unlocking this will probably be in the Sevii Islands.
* The legendary beasts need side and walking frames.

### Kanto
* The entire credits sequence has to be done.
* Janine does not have an OW sprite and is using Koga's as a placeholder.
* The Trainer House basement is not yet implemented.
* The Magnet Train is invisible and has no cutscene. Need Magnet Train revamped tiles.
* The Game Director and Artist in the Game Freak floor of Celadon Mansion need scripts.
   * Need Pokédex completion Diploma graphics for both the Johto and National Dex.
* Blue should use the Fly field move when flying away from Cinnabar Island. Currently, he teleports.

### Battle Frontier
###### *(Note, the Battle Frontier is technically available but is unplayable. Testers should not enter it, as it can trap the player and ruin saves.)*
* The indoor Battle Pyramid needs its tilesets configured and need to be mapped.
* The indoor Battle Factory needs its tileset configured and needs to be mapped.
* The indoor Battle Pike needs its tileset configured and needs to be mapped.
* The OW Frontier needs Day/Night palettes.
* All NPCs need to be replaced and given new dialogue to reflect 3 years passing (Some outdoor Battle Frontier West NPCs are done).
* Trainer rosters need to be fixed with correct classes and OW sprites. Sierra clobbered these when adding Johto trainer classes.
* All text strings need to be checked for overflow, as the FRLG textbox CD uses is smaller than the Emerald one.
* Add all Gen 3 tutor moves to the BP vendors.
* Make the decoration BP vendors give CD decorations instead of RSE Secret Base decorations.
* Figure out what is going on with the Frontier Pass. May just need to update its tilemap for the new Trainer Card graphics.
* Insert OW graphics for Peeko and Mr. Briney.

## Content outside of the current playable areas that is unfinished:
* The Sevii Islands are entirely absent. The event to unlock them is implemented, but dumps the player back to Cinnabar when triggered.
  * Will need new region maps for this as well.
* Pokémon Contests (which will show up in Sevii) will need their coordinators redone, as their OWs are likely not assigned correctly anymore. Will need to redo the whole roster of NPC contest mons and their trainers. Check to see if this is a problem for link contests where not all NPCs are replaced with players. If the selected NPCs/NPC mons and their entire data structure are not transfered over, then not having the same rosters available will break link contests with Emerald.

## Stuff that I may or may not want to implement:
* Should Vermilion Gym have its gym puzzle restored? Would need new dialogue for some of the NPCs there.
* Determine the most common substrings in dialogue and make more string placeholders out of them. Examples:
  * The string, "phone number" would save 440 bytes if turned into one.
  * "TEAM ROCKET" has 48 occurrences and could save 432 bytes if turned into one.
* A `buffermapname` scripting command has the potential to save hundreds of bytes.
* Sierra expressed interest in porting the dynamic OW palette system. Such a system would simplify implementing the Battle Frontier and eliminate the need for OW palette workarounds in the Ecruteak Dance Theater (Kimono Girls), Burned Tower (Rival/Eusine and gray beasts), and Cianwood (Eusine).
* Currently, all Pokémon OW sprites (save Clefairy for Mt. Moon Square) do not have walking frames, which is how FRLG did it. Perhaps make walking sprites for all of them. Most Pokémon do NOT walk around in the OW, as Crystal often used menu sprites which also did not have walking frames.
* There are sprites in the [#graphics channel](https://discord.com/channels/237788642238660610/671823652341284865) (specifically some of the Trainer sprites) that I'm not sure if they're in Sierra's master or not or if I should add them to the progress branch and ignore Sierra's efforts there.
* Sophia/Luna/Moriya's Pokémon sprite changes? Where are these PRed if they are PRed at all?
* What to do with the Gen 3 event islands?
  * Custom e-Reader cards could be cool for these unlocks since they are mentioned prominently in the National Park in lieu of the Gameboy Printer. Would need to reimplement e-Reader functionality for this. It is only partially present and isn't fully translated since it was in Japanese Emerald.

&nbsp;

&nbsp;

&nbsp;

&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
