#ifndef __ResourceLoader_h__
#define __ResourceLoader_h__

#include <ulib/ulib.h>
#include "Images.h"
#include <vector>
#include <string>

class ResourceLoader {
private:
	std::vector<UL_IMAGE*> loadedResources;
	static ResourceLoader* sSingleton;

public:
	
	static ResourceLoader* Get() {
		if(sSingleton==NULL) {
			sSingleton=new ResourceLoader();
		}
		return sSingleton;
	}

	void loadAll() {
		for(u32 i=0; i<getImagesSize(); i++) {
			loadedResources[images[i].ID] = ulLoadImageFilePNG(images[i].bytes, images[i].size, UL_IN_VRAM, UL_PF_PAL8);
		}
	}
	
	void dumpLoaded(int xbase, int ybase) {
		for(unsigned int i=0; i<getImagesSize(); i++) {
			ulPrintf_xy(xbase, ybase+=8, " %d %p ", i, getResource(i));
		}
	}
	
	UL_IMAGE* getResource(int ID) {
		return loadedResources[ID];
	}

};

ResourceLoader* ResourceLoader::sSingleton=NULL;

#endif
