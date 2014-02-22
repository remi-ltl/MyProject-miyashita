/*
 * Character.cpp
 *
 *  Created on: 2013/11/09
 *      Author: gameprogram
 */

#include "Character.h"


Character::Character() {
	// TODO 自動生成されたコンストラクター・スタブ
	setSpeed(0);
}

Character::~Character() {
	// TODO Auto-generated destructor stub
}

bool Character::load(const char* filename){
	return (this->initWithFile(filename));
}

void Character::update(float dt){

}

bool Character::CollisionSprite(Character* target,bool pp){
	bool isCollision = false;

	CCRect intersection;
	CCRect targetRect 	= target->boundingBox();
	CCRect myRect 		= this->boundingBox();

	if(targetRect.intersectsRect(myRect)){
		//透明部分を考慮しない時
		if(!pp){return true;}

		float tmpX;
		float tmpY;
		float tmpWidth;
		float tmpHeight;

		if(targetRect.getMaxX() > myRect.getMinX()){
			tmpX 	= myRect.getMinX();
			tmpWidth= targetRect.getMaxX() - myRect.getMinX();
		}
		else{
			tmpX 	= targetRect.getMinX();
			tmpWidth= myRect.getMaxX() - targetRect.getMinX();
		}

		if(targetRect.getMinY() < myRect.getMaxY()){
			tmpY 		= targetRect.getMinY();
			tmpHeight	= myRect.getMaxY() - targetRect.getMinY();
		}
		else{
			tmpY 		= myRect.getMinY();
			tmpHeight	= targetRect.getMaxY() - myRect.getMinY();
		}
		intersection = CCRectMake(	tmpX * CC_CONTENT_SCALE_FACTOR(),
									tmpY  * CC_CONTENT_SCALE_FACTOR(),
									tmpWidth * CC_CONTENT_SCALE_FACTOR(),
									tmpHeight * CC_CONTENT_SCALE_FACTOR());

        unsigned int x = intersection.origin.x;
        unsigned int y = intersection.origin.y;
        unsigned int w = intersection.size.width;
        unsigned int h = intersection.size.height;

        unsigned int numPixels = w * h;

        if (numPixels<=0) return false;

        // Draw into the RenderTexture
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCRenderTexture *rt = CCRenderTexture::create(size.width, size.height, kCCTexture2DPixelFormat_RGBA8888);
        rt->beginWithClear(0, 0, 0, 0);

        // Render both sprites: first one in RED and second one in GREEN
        glColorMask(1, 0, 0, 1);
        target->visit();
        glColorMask(0, 1, 0, 1);
        this->visit();
        glColorMask(1, 1, 1, 1);

        // Get color values of intersection area
        ccColor4B *buffer = (ccColor4B *)malloc( sizeof(ccColor4B) * numPixels );
        glReadPixels(x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

        rt->end();

        // Read buffer
        unsigned int step = 1;
        for(unsigned int i=0; i<numPixels; i+=step) {
            ccColor4B color = buffer[i];
            CCLOG("Pixel color: %d, %d, %d", color.r, color.g, color.b);
            if (color.r > 0 && color.g > 0) {
                isCollision = true;
                CCLOG("Colliding");
                break;
            }
        }

        // Free buffer memory
        free(buffer);
    }

    return isCollision;

}
