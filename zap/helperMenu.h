//-----------------------------------------------------------------------------------
//
// Bitfighter - A multiplayer vector graphics space game
// Based on Zap demo released for Torque Network Library by GarageGames.com
//
// Derivative work copyright (C) 2008-2009 Chris Eykamp
// Original work copyright (C) 2004 GarageGames.com, Inc.
// Other code copyright as noted
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful (and fun!),
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//------------------------------------------------------------------------------------

#ifndef _HELPERMENU_H_
#define _HELPERMENU_H_

#include "Engineerable.h"     // For EngineerBuildObjects enum
#include "InputCode.h"
#include "tnl.h"
#include "Color.h"
#include "Timer.h"

using namespace TNL; 


namespace Zap
{

class ClientGame;
class UIManager;
class HelperManager;


struct OverlayMenuItem
{
   InputCode key;             // Keyboard key used to select in menu
   InputCode button;          // Controller button used to select in menu
   bool showOnMenu;           // Should this item actually be added to the menu?
   const char *name;          // Name used on menu
   const Color *itemColor;
   const char *help;          // An additional bit of help text, also displayed on menu
   const Color *helpColor;    // Pointer to color with which to render the item
};


class HelperMenu
{
public:
   enum HelperMenuType {
      ChatHelperType,
      QuickChatHelperType,
      LoadoutHelperType,
      EngineerHelperType,
      ShuffleTeamsHelperType
   };

private:
   virtual const char *getCancelMessage();
   virtual InputCode getActivationKey();

   bool mActivating;    // True when menu is being activated, false when deactivating, undefined 

   ClientGame *mClientGame;
   HelperManager *mHelperManager;

protected:
   static const S32 MENU_TOP = 180;    // Location of top of overlay menu

   Timer mAnimationTimer;              // Timer for activation/deactivation animation

   S32 getLeftEdgeOfMenuPos();         // Return left edge of menu

   // Shortcut helper function
   virtual void exitHelper();

   void drawItemMenu(S32 xPos, S32 yPos, S32 width, const char *title, const OverlayMenuItem *items, S32 count,
                     const char **legendText = NULL, const Color **legendColors = NULL, S32 legendCount = 0);

   ClientGame *getGame();

   static const S32 MENU_FONT_SIZE        = 15;    // Size of standard items
   static const S32 MENU_FONT_SPACING     =  7;    // Vertical gap between lines
   static const S32 MENU_PADDING          =  3;
   static const S32 MENU_LEGEND_FONT_SIZE = 11;    // Smaller font of lengend items on QuickChat menus
   static const S32 ITEM_HELP_PADDING = 5;         // Gap between item and its help text
   static const S32 ITEM_INDENT = 50;              // Amount individual menu items are indented to make room for keys

public:
   explicit HelperMenu();     // Constructor
   virtual ~HelperMenu();     // Destructor

   void initialize(ClientGame *game, HelperManager *helperManager);

   virtual void render() = 0;
   virtual void idle(U32 delta);
   virtual void onActivated();

   bool isClosing() const;                         // Return true if menu is playing the closing animation
   F32 getFraction();                              // Get fraction of openness


   virtual bool processInputCode(InputCode inputCode);  
   virtual void onTextInput(char ascii);

   virtual void activateHelp(UIManager *uiManager);   // Open help to an appropriate page
   virtual bool isMovementDisabled();                 // Is ship movement disabled while this helper is active?
   virtual bool isChatDisabled();                     // Returns true if chat and friends should be disabled while this is active

   virtual S32 getActivationAnimationTime();          // Return 0 to disable animations
   S32 getWidth(const OverlayMenuItem *items, S32 count);

   virtual HelperMenuType getType() = 0;
};


};

#endif


