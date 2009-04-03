//-----------------------------------------------------------------------------------
//
// bitFighter - A multiplayer vector graphics space game
// Based on Zap demo released for Torque Network Library by GarageGames.com
//
// Derivative work copyright (C) 2008 Chris Eykamp
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

#ifndef _BOTNAVMESHZONES_H_
#define _BOTNAVMESHZONES_H_

#include "gameObject.h"
#include "gameType.h"
#include "gameNetInterface.h"
#include "UI.h"
#include "gameObjectRender.h"
#include "tnlNetBase.h"
#include "../glut/glutInclude.h"

namespace Zap
{

struct NeighboringZone
{
   U16 zoneID;
   Point borderStart;
   Point borderEnd;
   Point borderCenter;     // Simply a point half way between borderStart and borderEnd
   Point center;           // Center of zone
   F32 distTo;
};

class BotNavMeshZone : public GameObject
{

private:   
   typedef GameObject Parent;

Vector<Point> mPolyFill;      // Triangles used for rendering polygon fill

public:
   U16 mZoneID;

   BotNavMeshZone();       // Constructor
   ~BotNavMeshZone();      // Destructor

   void render();

   S32 getRenderSortValue();

   // Create objects from parameters stored in level file
   bool processArguments(S32 argc, const char **argv);

   void onAddedToGame(Game *theGame);
   Point getCenter();      // Return center of zone

   // Bounding box for quick collision-possibility elimination
   void computeExtent();

   // More precise boundary for precise collision detection
   bool getCollisionPoly(U32 state, Vector<Point> &polyPoints);

   // Only gets run on the server, never on client
   bool collide(GameObject *hitObject);

   // These methods will be empty later...
    U32 packUpdate(GhostConnection *connection, U32 updateMask, BitStream *stream);
   void unpackUpdate(GhostConnection *connection, BitStream *stream);

   Vector<Point> mPolyBounds;

   Vector<NeighboringZone> mNeighbors;        // List of other zones this zone touches
   S32 getNeighborIndex(S32 zone);           // Returns index of neighboring zone, or -1 if zone is not a neighbor

   static void buildBotNavMeshZoneConnections();

   TNL_DECLARE_CLASS(BotNavMeshZone);
};

extern Vector<SafePtr<BotNavMeshZone>> gBotNavMeshZones;     // List of all our zones



class AStar
{
private:
   static F32 heuristic(S32 fromZone, S32 toZone);
   static Point findGateway(S32 zone1, S32 zone2);

public:
   static Vector<Point> findPath (S32 startZone, S32 targetZone, Point target);
   
};


};


#endif

