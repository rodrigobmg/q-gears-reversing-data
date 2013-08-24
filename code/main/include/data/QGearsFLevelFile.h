/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2013-08-24 Tobias Peters <tobias.peters@kreativeffekt.at>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef __QGearsFLevelFile_H__
#define __QGearsFLevelFile_H__

#include <OgreResource.h>

#include "common/TypeDefine.h"

#include "QGearsBackgroundFile.h"
#include "QGearsPaletteFile.h"

namespace QGears
{
    class FLevelFile : public Ogre::Resource
    {
    public:

        FLevelFile( Ogre::ResourceManager *creator, const String &name
              ,Ogre::ResourceHandle handle, const String &group
              ,bool isManual = false, Ogre::ManualResourceLoader *loader = NULL );

        virtual ~FLevelFile();

        static const String RESOURCE_TYPE;

        virtual const BackgroundFilePtr&   getBackground( void ) const;
        virtual const PaletteFilePtr&      getPalette   ( void ) const;

        virtual void setBackground( const BackgroundFilePtr &background  );
        virtual void setPalette   ( const PaletteFilePtr    &palette     );

    protected:
        virtual void loadImpl( void );
        virtual void unloadImpl( void );
        virtual size_t calculateSize( void ) const;

        virtual const String& getResourceType( void ) const;
        virtual Ogre::DataStreamPtr openResource( void );

    private:
        BackgroundFilePtr   m_background;
        PaletteFilePtr      m_palette;
    };

    //-------------------------------------------------------------------------
    class FLevelFilePtr : public Ogre::SharedPtr<FLevelFile>
    {
    public:
        FLevelFilePtr() : Ogre::SharedPtr<FLevelFile>() {}
        explicit FLevelFilePtr( FLevelFile *rep ) : Ogre::SharedPtr<FLevelFile>(rep) {}
        FLevelFilePtr( const FLevelFilePtr &r ) : Ogre::SharedPtr<FLevelFile>(r) {}
        FLevelFilePtr( const Ogre::ResourcePtr &r ) : Ogre::SharedPtr<FLevelFile>()
        {
            if( r.isNull() )
                return;
            // lock & copy other mutex pointer
            OGRE_LOCK_MUTEX(*r.OGRE_AUTO_MUTEX_NAME)
            OGRE_COPY_AUTO_SHARED_MUTEX(r.OGRE_AUTO_MUTEX_NAME)
            pRep = static_cast<FLevelFile*>(r.getPointer());
            pUseCount = r.useCountPointer();
            useFreeMethod = r.freeMethod();
            if (pUseCount)
            {
                ++(*pUseCount);
            }
        }

        /// Operator used to convert a ResourcePtr to a FLevelFilePtr
        FLevelFilePtr& operator=( const Ogre::ResourcePtr& r )
        {
            if(pRep == static_cast<FLevelFile*>(r.getPointer()))
                return *this;
            release();
            if( r.isNull() )
                return *this; // resource ptr is null, so the call to release above has done all we need to do.
            // lock & copy other mutex pointer
            OGRE_LOCK_MUTEX(*r.OGRE_AUTO_MUTEX_NAME)
            OGRE_COPY_AUTO_SHARED_MUTEX(r.OGRE_AUTO_MUTEX_NAME)
            pRep = static_cast<FLevelFile*>(r.getPointer());
            pUseCount = r.useCountPointer();
            useFreeMethod = r.freeMethod();
            if (pUseCount)
            {
                ++(*pUseCount);
            }
            return *this;
        }
    };
}

#endif // __QGearsFLevelFile_H__
