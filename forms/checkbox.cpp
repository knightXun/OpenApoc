
#include "checkbox.h"
#include "../framework/framework.h"
#include "../game/resources/gamecore.h"

RawSound* CheckBox::buttonclick = nullptr;

CheckBox::CheckBox( Control* Owner ) : Control( Owner ), Checked(false), imagechecked(nullptr), imageunchecked(nullptr)
{
	LoadResources();
	if( buttonclick == nullptr )
	{
		buttonclick = new RawSound( "STRATEGC/INTRFACE/BUTTON1.RAW" );
	}
}

CheckBox::~CheckBox()
{
}

void CheckBox::LoadResources()
{
	if( imagechecked == nullptr )
	{
		imagechecked = GAMECORE->GetImage( "PCK:UFODATA/ICONS.PCK:UFODATA/ICONS.TAB:39:UFODATA/PAL_01.DAT" );
		if( Size.X == 0 )
		{
			Size.X = al_get_bitmap_width( imagechecked );
		}
		if( Size.Y == 0 )
		{
			Size.Y = al_get_bitmap_height( imagechecked );
		}
	}
	if( imageunchecked == nullptr )
	{
		imageunchecked = GAMECORE->GetImage( "PCK:UFODATA/ICONS.PCK:UFODATA/ICONS.TAB:38:UFODATA/PAL_01.DAT" );
	}
}

void CheckBox::EventOccured( Event* e )
{
	Control::EventOccured( e );

	if( e->Type == EVENT_FORM_INTERACTION && e->Data.Forms.RaisedBy == this && e->Data.Forms.EventFlag == FormEventType::MouseDown )
	{
		buttonclick->PlaySound();
	}

	if( e->Type == EVENT_FORM_INTERACTION && e->Data.Forms.RaisedBy == this && e->Data.Forms.EventFlag == FormEventType::MouseClick )
	{
		Checked = !Checked;
		Event* ce = new Event();
		ce->Type = e->Type;
		memcpy( (void*)&(ce->Data.Forms), (void*)&(e->Data.Forms), sizeof( FRAMEWORK_FORMS_EVENT ) );
		ce->Data.Forms.EventFlag = FormEventType::CheckBoxChange;
		FRAMEWORK->PushEvent( ce );
	}
}

void CheckBox::Render()
{
	ALLEGRO_BITMAP* useimage;

	LoadResources();

	useimage = ( Checked ? imagechecked : imageunchecked);

	if( useimage != nullptr )
	{
		int bmpw = al_get_bitmap_width( useimage );
		int bmph = al_get_bitmap_height( useimage );
		if( bmpw == Size.X && bmph == Size.Y )
		{
			al_draw_bitmap( useimage, resolvedLocation.X, resolvedLocation.Y, 0 );
		} else {
			al_draw_scaled_bitmap( useimage, 0, 0, bmpw, bmph, resolvedLocation.X, resolvedLocation.Y, this->Size.X, this->Size.Y, 0 );
		}
	}

	PostRender();
}

void CheckBox::Update()
{
	Control::Update();
}

void CheckBox::UnloadResources()
{
	if( imagechecked != nullptr )
	{
		al_destroy_bitmap( imagechecked );
		imagechecked = nullptr;
	}
	if( imageunchecked != nullptr )
	{
		al_destroy_bitmap( imageunchecked );
		imageunchecked = nullptr;
	}
	Control::UnloadResources();
}