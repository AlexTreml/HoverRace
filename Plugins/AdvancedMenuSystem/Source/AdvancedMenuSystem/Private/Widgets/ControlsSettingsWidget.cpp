//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//


#include "Widgets/ControlsSettingsWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Font.h"

UControlsSettingsWidget::UControlsSettingsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> AICON(TEXT("/Script/Engine.Texture2D'/Engine/EngineResources/AICON-Green.AICON-Green'"));

	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> TileMat(TEXT("Material'/AdvancedMenuSystem/Demo/Materials/M_Tile.M_Tile'"));
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(*UWidget::GetDefaultFontName());
		FSlateFontInfo DefaultFont = FSlateFontInfo(RobotoFontObj.Object, 24, FName("Bold"));

		TitleTextFont = DefaultFont;
	}

	//Mouse
	FButtonIcon LeftMouseButton;
	LeftMouseButton.KeyDisplayName = FText::AsCultureInvariant(("Left Mouse Button"));
	ButtonIcons.Add(LeftMouseButton);

	FButtonIcon RightMouseButton;
	RightMouseButton.KeyDisplayName = FText::AsCultureInvariant(("Right Mouse Button"));
	ButtonIcons.Add(RightMouseButton);

	FButtonIcon MiddleMouseButton;
	MiddleMouseButton.KeyDisplayName = FText::AsCultureInvariant(("Middle Mouse Button"));
	ButtonIcons.Add(MiddleMouseButton);

	FButtonIcon ThumbMouseButton;
	ThumbMouseButton.KeyDisplayName = FText::AsCultureInvariant(("Thumb Mouse Button"));
	ButtonIcons.Add(ThumbMouseButton);

	FButtonIcon ThumbMouseButton2;
	ThumbMouseButton2.KeyDisplayName = FText::AsCultureInvariant(("Thumb Mouse Button 2"));
	ButtonIcons.Add(ThumbMouseButton2);

	//
	FButtonIcon Tab;
	Tab.KeyDisplayName = FText::AsCultureInvariant(("Tab"));
	ButtonIcons.Add(Tab);

	FButtonIcon Enter;
	Enter.KeyDisplayName = FText::AsCultureInvariant(("Enter"));
	ButtonIcons.Add(Enter);

	FButtonIcon Pause;
	Pause.KeyDisplayName = FText::AsCultureInvariant(("Pause"));
	ButtonIcons.Add(Pause);

	FButtonIcon CapsLock;
	CapsLock.KeyDisplayName = FText::AsCultureInvariant(("Caps Lock"));
	ButtonIcons.Add(CapsLock);

	FButtonIcon Escape;
	Escape.KeyDisplayName = FText::AsCultureInvariant(("Escape"));
	ButtonIcons.Add(Escape);
	
	FButtonIcon SpaceBar;
	SpaceBar.KeyDisplayName = FText::AsCultureInvariant(("Space Bar"));
	ButtonIcons.Add(SpaceBar);

	FButtonIcon PageUp;
	PageUp.KeyDisplayName = FText::AsCultureInvariant(("Page Up"));
	ButtonIcons.Add(PageUp);

	FButtonIcon PageDown;
	PageDown.KeyDisplayName = FText::AsCultureInvariant(("Page Down"));
	ButtonIcons.Add(PageDown);

	FButtonIcon End;
	End.KeyDisplayName = FText::AsCultureInvariant(("End"));
	ButtonIcons.Add(End);

	FButtonIcon Home;
	Home.KeyDisplayName = FText::AsCultureInvariant(("Home"));
	ButtonIcons.Add(Home);

	FButtonIcon Left;
	Left.KeyDisplayName = FText::AsCultureInvariant(("Left"));
	ButtonIcons.Add(Left);

	FButtonIcon Up;
	Up.KeyDisplayName = FText::AsCultureInvariant(("Up"));
	ButtonIcons.Add(Up);

	FButtonIcon Right;
	Right.KeyDisplayName = FText::AsCultureInvariant(("Right"));
	ButtonIcons.Add(Right);

	FButtonIcon Down;
	Down.KeyDisplayName = FText::AsCultureInvariant(("Down"));
	ButtonIcons.Add(Down);

	FButtonIcon Insert;
	Insert.KeyDisplayName = FText::AsCultureInvariant(("Insert"));
	ButtonIcons.Add(Insert);

	FButtonIcon Backspace;
	FButtonIcon Delete;


#if PLATFORM_MAC
	Backspace.KeyDisplayName = FText::AsCultureInvariant(("Delete"));
	Delete.KeyDisplayName = FText::AsCultureInvariant(("ForwardDelete"));
#else
	Backspace.KeyDisplayName = FText::AsCultureInvariant(("Backspace"));
	Delete.KeyDisplayName = FText::AsCultureInvariant(("Delete"));
#endif

	ButtonIcons.Add(Backspace);
	ButtonIcons.Add(Delete);

	//0 1 2 ...
	FButtonIcon Zero;
	Zero.KeyDisplayName = FText::AsCultureInvariant(("0"));
	ButtonIcons.Add(Zero);

	FButtonIcon One;
	One.KeyDisplayName = FText::AsCultureInvariant(("1"));
	ButtonIcons.Add(One);

	FButtonIcon Two;
	Two.KeyDisplayName = FText::AsCultureInvariant(("2"));
	ButtonIcons.Add(Two);

	FButtonIcon Three;
	Three.KeyDisplayName = FText::AsCultureInvariant(("3"));
	ButtonIcons.Add(Three);

	FButtonIcon Four;
	Four.KeyDisplayName = FText::AsCultureInvariant(("4"));
	ButtonIcons.Add(Four);

	FButtonIcon Five;
	Five.KeyDisplayName = FText::AsCultureInvariant(("5"));
	ButtonIcons.Add(Five);

	FButtonIcon Six;
	Six.KeyDisplayName = FText::AsCultureInvariant(("6"));
	ButtonIcons.Add(Six);

	FButtonIcon Seven;
	Seven.KeyDisplayName = FText::AsCultureInvariant(("7"));
	ButtonIcons.Add(Seven);

	FButtonIcon Eight;
	Eight.KeyDisplayName = FText::AsCultureInvariant(("8"));
	ButtonIcons.Add(Eight);

	FButtonIcon Nine;
	Nine.KeyDisplayName = FText::AsCultureInvariant(("9"));
	ButtonIcons.Add(Nine);

	//abc..

	FButtonIcon A;
	A.KeyDisplayName = FText::AsCultureInvariant(("A"));
	ButtonIcons.Add(A);

	FButtonIcon B;
	B.KeyDisplayName = FText::AsCultureInvariant(("B"));
	ButtonIcons.Add(B);

	FButtonIcon C;
	C.KeyDisplayName = FText::AsCultureInvariant(("C"));
	ButtonIcons.Add(C);

	FButtonIcon D;
	D.KeyDisplayName = FText::AsCultureInvariant(("D"));
	ButtonIcons.Add(D);

	FButtonIcon E;
	E.KeyDisplayName = FText::AsCultureInvariant(("E"));
	ButtonIcons.Add(E);

	FButtonIcon F;
	F.KeyDisplayName = FText::AsCultureInvariant(("F"));
	ButtonIcons.Add(F);

	FButtonIcon G;
	G.KeyDisplayName = FText::AsCultureInvariant(("G"));
	ButtonIcons.Add(G);

	FButtonIcon H;
	H.KeyDisplayName = FText::AsCultureInvariant(("H"));
	ButtonIcons.Add(H);

	FButtonIcon I;
	I.KeyDisplayName = FText::AsCultureInvariant(("I"));
	ButtonIcons.Add(I);

	FButtonIcon J;
	J.KeyDisplayName = FText::AsCultureInvariant(("J"));
	ButtonIcons.Add(J);

	FButtonIcon K;
	K.KeyDisplayName = FText::AsCultureInvariant(("K"));
	ButtonIcons.Add(K);

	FButtonIcon L;
	L.KeyDisplayName = FText::AsCultureInvariant(("L"));
	ButtonIcons.Add(L);

	FButtonIcon M;
	M.KeyDisplayName = FText::AsCultureInvariant(("M"));
	ButtonIcons.Add(M);

	FButtonIcon N;
	N.KeyDisplayName = FText::AsCultureInvariant(("N"));
	ButtonIcons.Add(N);

	FButtonIcon O;
	O.KeyDisplayName = FText::AsCultureInvariant(("O"));
	ButtonIcons.Add(O);

	FButtonIcon P;
	P.KeyDisplayName = FText::AsCultureInvariant(("P"));
	ButtonIcons.Add(P);

	FButtonIcon Q;
	Q.KeyDisplayName = FText::AsCultureInvariant(("Q"));
	ButtonIcons.Add(Q);

	FButtonIcon R;
	R.KeyDisplayName = FText::AsCultureInvariant(("R"));
	ButtonIcons.Add(R);

	FButtonIcon S;
	S.KeyDisplayName = FText::AsCultureInvariant(("S"));
	ButtonIcons.Add(S);

	FButtonIcon T;
	T.KeyDisplayName = FText::AsCultureInvariant(("T"));
	ButtonIcons.Add(T);

	FButtonIcon U;
	U.KeyDisplayName = FText::AsCultureInvariant(("U"));
	ButtonIcons.Add(U);

	FButtonIcon V;
	V.KeyDisplayName = FText::AsCultureInvariant(("V"));
	ButtonIcons.Add(V);

	FButtonIcon W;
	W.KeyDisplayName = FText::AsCultureInvariant(("W"));
	ButtonIcons.Add(W);

	FButtonIcon X;
	X.KeyDisplayName = FText::AsCultureInvariant(("X"));
	ButtonIcons.Add(X);

	FButtonIcon Y;
	Y.KeyDisplayName = FText::AsCultureInvariant(("Y"));
	ButtonIcons.Add(Y);

	FButtonIcon Z;
	Z.KeyDisplayName = FText::AsCultureInvariant(("Z"));
	ButtonIcons.Add(Z);

	//Numpad

	FButtonIcon NumPadZero;
	NumPadZero.KeyDisplayName = FText::AsCultureInvariant(("NumPadZero"));
	ButtonIcons.Add(NumPadZero);

	FButtonIcon NumPadOne;
	NumPadOne.KeyDisplayName = FText::AsCultureInvariant(("NumPadOne"));
	ButtonIcons.Add(NumPadOne);

	FButtonIcon NumPadTwo;
	NumPadTwo.KeyDisplayName = FText::AsCultureInvariant(("NumPadTwo"));
	ButtonIcons.Add(NumPadTwo);

	FButtonIcon NumPadThree;
	NumPadThree.KeyDisplayName = FText::AsCultureInvariant(("NumPadThree"));
	ButtonIcons.Add(NumPadThree);

	FButtonIcon NumPadFour;
	NumPadFour.KeyDisplayName = FText::AsCultureInvariant(("NumPadFour"));
	ButtonIcons.Add(NumPadFour);

	FButtonIcon NumPadFive;
	NumPadFive.KeyDisplayName = FText::AsCultureInvariant(("NumPadFive"));
	ButtonIcons.Add(NumPadFive);

	FButtonIcon NumPadSix;
	NumPadSix.KeyDisplayName = FText::AsCultureInvariant(("NumPadSix"));
	ButtonIcons.Add(NumPadSix);

	FButtonIcon NumPadSeven;
	NumPadSeven.KeyDisplayName = FText::AsCultureInvariant(("NumPadSeven"));
	ButtonIcons.Add(NumPadSeven);

	FButtonIcon NumPadEight;
	NumPadEight.KeyDisplayName = FText::AsCultureInvariant(("NumPadEight"));
	ButtonIcons.Add(NumPadEight);

	FButtonIcon NumPadNine;
	NumPadNine.KeyDisplayName = FText::AsCultureInvariant(("NumPadNine"));
	ButtonIcons.Add(NumPadNine);

	//Num math
	
	FButtonIcon Multiply;
	Multiply.KeyDisplayName = FText::AsCultureInvariant(("Multiply"));
	ButtonIcons.Add(Multiply);

	FButtonIcon Add;
	Add.KeyDisplayName = FText::AsCultureInvariant(("Add"));
	ButtonIcons.Add(Add);

	FButtonIcon Subtract;
	Subtract.KeyDisplayName = FText::AsCultureInvariant(("Subtract"));
	ButtonIcons.Add(Subtract);

	FButtonIcon Decimal;
	Decimal.KeyDisplayName = FText::AsCultureInvariant(("Decimal"));
	ButtonIcons.Add(Decimal);

	FButtonIcon Divide;
	Divide.KeyDisplayName = FText::AsCultureInvariant(("Divide"));
	ButtonIcons.Add(Divide);

	//F*

	FButtonIcon F1;
	F1.KeyDisplayName = FText::AsCultureInvariant(("F1"));
	ButtonIcons.Add(F1);

	FButtonIcon F2;
	F2.KeyDisplayName = FText::AsCultureInvariant(("F2"));
	ButtonIcons.Add(F2);

	FButtonIcon F3;
	F3.KeyDisplayName = FText::AsCultureInvariant(("F3"));
	ButtonIcons.Add(F3);

	FButtonIcon F4;
	F4.KeyDisplayName = FText::AsCultureInvariant(("F4"));
	ButtonIcons.Add(F4);

	FButtonIcon F5;
	F5.KeyDisplayName = FText::AsCultureInvariant(("F5"));
	ButtonIcons.Add(F5);

	FButtonIcon F6;
	F6.KeyDisplayName = FText::AsCultureInvariant(("F6"));
	ButtonIcons.Add(F6);

	FButtonIcon F7;
	F7.KeyDisplayName = FText::AsCultureInvariant(("F7"));
	ButtonIcons.Add(F7);

	FButtonIcon F8;
	F8.KeyDisplayName = FText::AsCultureInvariant(("F8"));
	ButtonIcons.Add(F8);

	FButtonIcon F9;
	F9.KeyDisplayName = FText::AsCultureInvariant(("F9"));
	ButtonIcons.Add(F9);

	FButtonIcon F10;
	F10.KeyDisplayName = FText::AsCultureInvariant(("F10"));
	ButtonIcons.Add(F10);

	FButtonIcon F11;
	F11.KeyDisplayName = FText::AsCultureInvariant(("F11"));
	ButtonIcons.Add(F11);

	FButtonIcon F12;
	F12.KeyDisplayName = FText::AsCultureInvariant(("F12"));
	ButtonIcons.Add(F12);

	//Other 
	FButtonIcon NumLock;
	NumLock.KeyDisplayName = FText::AsCultureInvariant(("NumLock"));
	ButtonIcons.Add(NumLock);

	FButtonIcon ScrollLock;
	ScrollLock.KeyDisplayName = FText::AsCultureInvariant(("ScrollLock"));
	ButtonIcons.Add(ScrollLock);

	FButtonIcon LeftShift;
	LeftShift.KeyDisplayName = FText::AsCultureInvariant(("Left Shift"));
	ButtonIcons.Add(LeftShift);

	FButtonIcon RightShift;
	RightShift.KeyDisplayName = FText::AsCultureInvariant(("Right Shift"));
	ButtonIcons.Add(RightShift);

	FButtonIcon LeftControl;
	LeftControl.KeyDisplayName = FText::AsCultureInvariant(("Left Control"));
	ButtonIcons.Add(LeftControl);

	FButtonIcon RightControl;
	RightControl.KeyDisplayName = FText::AsCultureInvariant(("Right Control"));
	ButtonIcons.Add(RightControl);

	FButtonIcon LeftAlt;
	LeftAlt.KeyDisplayName = FText::AsCultureInvariant(("Left Alt"));
	ButtonIcons.Add(LeftAlt);

	FButtonIcon RightAlt;
	RightAlt.KeyDisplayName = FText::AsCultureInvariant(("Right Alt"));
	ButtonIcons.Add(RightAlt);

	FButtonIcon LeftCommand;
	LeftCommand.KeyDisplayName = FText::AsCultureInvariant(("Left Command"));
	ButtonIcons.Add(LeftCommand);

	FButtonIcon RightCommand;
	RightCommand.KeyDisplayName = FText::AsCultureInvariant(("Right Command"));
	ButtonIcons.Add(RightCommand);

	FButtonIcon Semicolon;
	Semicolon.KeyDisplayName = FText::AsCultureInvariant(("Semicolon"));
	ButtonIcons.Add(Semicolon);

	FButtonIcon Equals;
	Equals.KeyDisplayName = FText::AsCultureInvariant(("Equals"));
	ButtonIcons.Add(Equals);

	FButtonIcon Comma;
	Comma.KeyDisplayName = FText::AsCultureInvariant(("Comma"));
	ButtonIcons.Add(Comma);

	FButtonIcon Hyphen;
	Hyphen.KeyDisplayName = FText::AsCultureInvariant(("Hyphen"));
	ButtonIcons.Add(Hyphen);

	FButtonIcon Underscore;
	Underscore.KeyDisplayName = FText::AsCultureInvariant(("Underscore"));
	ButtonIcons.Add(Underscore);

	FButtonIcon Period;
	Period.KeyDisplayName = FText::AsCultureInvariant(("Period"));
	ButtonIcons.Add(Period);

	FButtonIcon Slash;
	Slash.KeyDisplayName = FText::AsCultureInvariant(("Slash"));
	ButtonIcons.Add(Slash);

	FButtonIcon Tilde;
	Tilde.KeyDisplayName = FText::AsCultureInvariant(("Tilde"));
	ButtonIcons.Add(Tilde);

	FButtonIcon LeftBracket;
	LeftBracket.KeyDisplayName = FText::AsCultureInvariant(("LeftBracket"));
	ButtonIcons.Add(LeftBracket);

	FButtonIcon Backslash;
	Backslash.KeyDisplayName = FText::AsCultureInvariant(("Backslash"));
	ButtonIcons.Add(Backslash);

	FButtonIcon RightBracket;
	RightBracket.KeyDisplayName = FText::AsCultureInvariant(("RightBracket"));
	ButtonIcons.Add(RightBracket);

	FButtonIcon Apostrophe;
	Apostrophe.KeyDisplayName = FText::AsCultureInvariant(("Apostrophe"));
	ButtonIcons.Add(Apostrophe);

	FButtonIcon Quote;
	Quote.KeyDisplayName = FText::AsCultureInvariant(("Quote"));
	ButtonIcons.Add(Quote);

	FButtonIcon LeftParantheses;
	LeftParantheses.KeyDisplayName = FText::AsCultureInvariant(("Left Parantheses"));
	ButtonIcons.Add(LeftParantheses);

	FButtonIcon RightParantheses;
	RightParantheses.KeyDisplayName = FText::AsCultureInvariant(("Right Parantheses"));
	ButtonIcons.Add(RightParantheses);

	FButtonIcon Ampersand;
	Ampersand.KeyDisplayName = FText::AsCultureInvariant(("Ampersand"));
	ButtonIcons.Add(Ampersand);

	FButtonIcon Asterix;
	Asterix.KeyDisplayName = FText::AsCultureInvariant(("Asterix"));
	ButtonIcons.Add(Asterix);

	FButtonIcon Caret;
	Caret.KeyDisplayName = FText::AsCultureInvariant(("Caret"));
	ButtonIcons.Add(Caret);

	FButtonIcon Dollar;
	Dollar.KeyDisplayName = FText::AsCultureInvariant(("Dollar"));
	ButtonIcons.Add(Dollar);

	FButtonIcon Exclamation;
	Exclamation.KeyDisplayName = FText::AsCultureInvariant(("Exclamation"));
	ButtonIcons.Add(Exclamation);

	FButtonIcon Colon;
	Colon.KeyDisplayName = FText::AsCultureInvariant(("Colon"));
	ButtonIcons.Add(Colon);

	// Setup Gamepad keys

	FButtonIcon Gamepad_DPad_Up;
	Gamepad_DPad_Up.KeyDisplayName = FText::AsCultureInvariant(("Gamepad DPad Up"));
	ButtonIcons.Add(Gamepad_DPad_Up);

	FButtonIcon Gamepad_DPad_Down;
	Gamepad_DPad_Down.KeyDisplayName = FText::AsCultureInvariant(("Gamepad DPad Down"));
	ButtonIcons.Add(Gamepad_DPad_Down);

	FButtonIcon Gamepad_DPad_Right;
	Gamepad_DPad_Right.KeyDisplayName = FText::AsCultureInvariant(("Gamepad DPad Right"));
	ButtonIcons.Add(Gamepad_DPad_Right);

	FButtonIcon Gamepad_DPad_Left;
	Gamepad_DPad_Left.KeyDisplayName = FText::AsCultureInvariant(("Gamepad DPad Left"));
	ButtonIcons.Add(Gamepad_DPad_Left);

	// Virtual key codes used for input axis button press/release emulation

	FButtonIcon Gamepad_LeftStick_Up;
	Gamepad_LeftStick_Up.KeyDisplayName = FText::AsCultureInvariant(("Gamepad LeftStick Up"));
	ButtonIcons.Add(Gamepad_LeftStick_Up);

	FButtonIcon Gamepad_LeftStick_Down;
	Gamepad_LeftStick_Down.KeyDisplayName = FText::AsCultureInvariant(("Gamepad LeftStick Down"));
	ButtonIcons.Add(Gamepad_LeftStick_Down);

	FButtonIcon Gamepad_LeftStick_Right;
	Gamepad_LeftStick_Right.KeyDisplayName = FText::AsCultureInvariant(("Gamepad LeftStick Right"));
	ButtonIcons.Add(Gamepad_LeftStick_Right);

	FButtonIcon Gamepad_LeftStick_Left;
	Gamepad_LeftStick_Left.KeyDisplayName = FText::AsCultureInvariant(("Gamepad LeftStick Left"));
	ButtonIcons.Add(Gamepad_LeftStick_Left);

	FButtonIcon Gamepad_Special_Left;
	Gamepad_Special_Left.KeyDisplayName = FText::AsCultureInvariant(("Gamepad Special Left"));
	ButtonIcons.Add(Gamepad_Special_Left);

	FButtonIcon Gamepad_Special_Right;
	Gamepad_Special_Right.KeyDisplayName = FText::AsCultureInvariant(("Gamepad Special Right"));
	ButtonIcons.Add(Gamepad_Special_Right);

	FButtonIcon Gamepad_FaceButton_Bottom;
	Gamepad_FaceButton_Bottom.KeyDisplayName = FText::AsCultureInvariant(("Gamepad FaceButton Bottom"));
	ButtonIcons.Add(Gamepad_FaceButton_Bottom);

	FButtonIcon Gamepad_FaceButton_Right;
	Gamepad_FaceButton_Right.KeyDisplayName = FText::AsCultureInvariant(("Gamepad FaceButton Right"));
	ButtonIcons.Add(Gamepad_FaceButton_Right);

	FButtonIcon Gamepad_FaceButton_Left;
	Gamepad_FaceButton_Left.KeyDisplayName = FText::AsCultureInvariant(("Gamepad FaceButton Left"));
	ButtonIcons.Add(Gamepad_FaceButton_Left);

	FButtonIcon Gamepad_FaceButton_Top;
	Gamepad_FaceButton_Top.KeyDisplayName = FText::AsCultureInvariant(("Gamepad FaceButton Top"));
	ButtonIcons.Add(Gamepad_FaceButton_Top);

	FButtonIcon Gamepad_LeftShoulder;
	Gamepad_LeftShoulder.KeyDisplayName = FText::AsCultureInvariant(("Gamepad Left Shoulder"));
	ButtonIcons.Add(Gamepad_LeftShoulder);

	FButtonIcon Gamepad_RightShoulder;
	Gamepad_RightShoulder.KeyDisplayName = FText::AsCultureInvariant(("Gamepad Right Shoulder"));
	ButtonIcons.Add(Gamepad_RightShoulder);

	FButtonIcon Gamepad_LeftTrigger;
	Gamepad_LeftTrigger.KeyDisplayName = FText::AsCultureInvariant(("Gamepad Left Trigger"));
	ButtonIcons.Add(Gamepad_LeftTrigger);

	FButtonIcon Gamepad_RightTrigger;
	Gamepad_RightTrigger.KeyDisplayName = FText::AsCultureInvariant(("Gamepad Right Trigger"));
	ButtonIcons.Add(Gamepad_RightTrigger);

	FButtonIcon Gamepad_LeftThumbstick;
	Gamepad_LeftThumbstick.KeyDisplayName = FText::AsCultureInvariant(("Gamepad Left Thumbstick"));
	ButtonIcons.Add(Gamepad_LeftThumbstick);

	FButtonIcon Gamepad_RightThumbstick;
	Gamepad_RightThumbstick.KeyDisplayName = FText::AsCultureInvariant(("Gamepad Right Thumbstick"));
	ButtonIcons.Add(Gamepad_RightThumbstick);

	// Fingers

	// Gestures

	FButtonIcon Gesture_Pinch;
	Gesture_Pinch.KeyDisplayName = FText::AsCultureInvariant(("Pinch"));
	ButtonIcons.Add(Gesture_Pinch);

	FButtonIcon Gesture_Flick;
	Gesture_Flick.KeyDisplayName = FText::AsCultureInvariant(("Flick"));
	ButtonIcons.Add(Gesture_Flick);

	FButtonIcon Gesture_Rotate;
	Gesture_Rotate.KeyDisplayName = FText::AsCultureInvariant(("Rotate"));
	ButtonIcons.Add(Gesture_Rotate);
	// PS4-specific

	// Steam Controller specific

	FButtonIcon Steam_Touch_0;
	Steam_Touch_0.KeyDisplayName = FText::AsCultureInvariant(("Steam Touch 0"));
	ButtonIcons.Add(Steam_Touch_0);

	FButtonIcon Steam_Touch_1;
	Steam_Touch_1.KeyDisplayName = FText::AsCultureInvariant(("Steam Touch 1"));
	ButtonIcons.Add(Steam_Touch_1);

	FButtonIcon Steam_Touch_2;
	Steam_Touch_2.KeyDisplayName = FText::AsCultureInvariant(("Steam Touch 2"));
	ButtonIcons.Add(Steam_Touch_2);

	FButtonIcon Steam_Touch_3;
	Steam_Touch_3.KeyDisplayName = FText::AsCultureInvariant(("Steam Touch 3"));
	ButtonIcons.Add(Steam_Touch_3);

	FButtonIcon Steam_Back_Left;
	Steam_Back_Left.KeyDisplayName = FText::AsCultureInvariant(("Steam Back Left"));
	ButtonIcons.Add(Steam_Back_Left);

	FButtonIcon Steam_Back_Right;
	Steam_Back_Right.KeyDisplayName = FText::AsCultureInvariant(("Steam Back Right"));
	ButtonIcons.Add(Steam_Back_Right);

	// Xbox One global speech commands

	FButtonIcon Global_Menu;
	Global_Menu.KeyDisplayName = FText::AsCultureInvariant(("Global Menu"));
	ButtonIcons.Add(Global_Menu);

	FButtonIcon Global_View;
	Global_View.KeyDisplayName = FText::AsCultureInvariant(("Global View"));
	ButtonIcons.Add(Global_View);

	FButtonIcon Global_Pause;
	Global_Pause.KeyDisplayName = FText::AsCultureInvariant(("Global Pause"));
	ButtonIcons.Add(Global_Pause);

	FButtonIcon Global_Play;
	Global_Play.KeyDisplayName = FText::AsCultureInvariant(("Global Play"));
	ButtonIcons.Add(Global_Play);

	FButtonIcon Global_Back;
	Global_Back.KeyDisplayName = FText::AsCultureInvariant(("Global Back"));
	ButtonIcons.Add(Global_Back);

	// Android-specific

	FButtonIcon Android_Back;
	Android_Back.KeyDisplayName = FText::AsCultureInvariant(("Android Back"));
	ButtonIcons.Add(Android_Back);

	FButtonIcon Android_Volume_Up;
	Android_Volume_Up.KeyDisplayName = FText::AsCultureInvariant(("Android Volume Up"));
	ButtonIcons.Add(Android_Volume_Up);

	FButtonIcon Android_Volume_Down;
	Android_Volume_Down.KeyDisplayName = FText::AsCultureInvariant(("Android Volume Down"));
	ButtonIcons.Add(Android_Volume_Down);

	FButtonIcon Android_Menu;
	Android_Menu.KeyDisplayName = FText::AsCultureInvariant(("Android Menu"));
	ButtonIcons.Add(Android_Menu);

	// HTC Vive Controller

	FButtonIcon Vive_Left_Grip_Click;
	Vive_Left_Grip_Click.KeyDisplayName = FText::AsCultureInvariant(("Vive Left Grip Click"));
	ButtonIcons.Add(Vive_Left_Grip_Click);

	FButtonIcon Vive_Left_Menu_Click;
	Vive_Left_Menu_Click.KeyDisplayName = FText::AsCultureInvariant(("Vive Left Menu Click"));
	ButtonIcons.Add(Vive_Left_Menu_Click);

	FButtonIcon Vive_Left_Trigger_Click;
	Vive_Left_Trigger_Click.KeyDisplayName = FText::AsCultureInvariant(("Vive Left Trigger Click"));
	ButtonIcons.Add(Vive_Left_Trigger_Click);

	FButtonIcon Vive_Left_Trackpad_Click;
	Vive_Left_Trackpad_Click.KeyDisplayName = FText::AsCultureInvariant(("Vive Left Trackpad Click"));
	ButtonIcons.Add(Vive_Left_Trackpad_Click);

	FButtonIcon Vive_Left_Trackpad_Touch;
	Vive_Left_Trackpad_Touch.KeyDisplayName = FText::AsCultureInvariant(("Vive Left Trackpad Touch"));
	ButtonIcons.Add(Vive_Left_Trackpad_Touch);

	FButtonIcon Vive_Left_Trackpad_Up;
	Vive_Left_Trackpad_Up.KeyDisplayName = FText::AsCultureInvariant(("Vive Left Trackpad Up"));
	ButtonIcons.Add(Vive_Left_Trackpad_Up);

	FButtonIcon Vive_Left_Trackpad_Down;
	Vive_Left_Trackpad_Down.KeyDisplayName = FText::AsCultureInvariant(("Vive Left Trackpad Down"));
	ButtonIcons.Add(Vive_Left_Trackpad_Down);

	FButtonIcon Vive_Left_Trackpad_Left;
	Vive_Left_Trackpad_Left.KeyDisplayName = FText::AsCultureInvariant(("Vive Left Trackpad Left"));
	ButtonIcons.Add(Vive_Left_Trackpad_Left);

	FButtonIcon Vive_Left_Trackpad_Right;
	Vive_Left_Trackpad_Right.KeyDisplayName = FText::AsCultureInvariant(("Vive Left Trackpad Right"));
	ButtonIcons.Add(Vive_Left_Trackpad_Right);

	FButtonIcon Vive_Right_Grip_Click;
	Vive_Right_Grip_Click.KeyDisplayName = FText::AsCultureInvariant(("Vive Right Grip Click"));
	ButtonIcons.Add(Vive_Right_Grip_Click);

	FButtonIcon Vive_Right_Menu_Click;
	Vive_Right_Menu_Click.KeyDisplayName = FText::AsCultureInvariant(("Vive Right Menu Click"));
	ButtonIcons.Add(Vive_Right_Menu_Click);

	FButtonIcon Vive_Right_Trigger_Click;
	Vive_Right_Trigger_Click.KeyDisplayName = FText::AsCultureInvariant(("Vive Right Trigger Click"));
	ButtonIcons.Add(Vive_Right_Trigger_Click);

	FButtonIcon Vive_Right_Trackpad_Click;
	Vive_Right_Trackpad_Click.KeyDisplayName = FText::AsCultureInvariant(("Vive Right Trackpad Click"));
	ButtonIcons.Add(Vive_Right_Trackpad_Click);

	FButtonIcon Vive_Right_Trackpad_Touch;
	Vive_Right_Trackpad_Touch.KeyDisplayName = FText::AsCultureInvariant(("Vive Right Trackpad Touch"));
	ButtonIcons.Add(Vive_Right_Trackpad_Touch);

	FButtonIcon Vive_Right_Trackpad_Up;
	Vive_Right_Trackpad_Up.KeyDisplayName = FText::AsCultureInvariant(("Vive Right Trackpad Up"));
	ButtonIcons.Add(Vive_Right_Trackpad_Up);

	FButtonIcon Vive_Right_Trackpad_Down;
	Vive_Right_Trackpad_Down.KeyDisplayName = FText::AsCultureInvariant(("Vive Right Trackpad Down"));
	ButtonIcons.Add(Vive_Right_Trackpad_Down);

	FButtonIcon Vive_Right_Trackpad_Left;
	Vive_Right_Trackpad_Left.KeyDisplayName = FText::AsCultureInvariant(("Vive Right Trackpad Left"));
	ButtonIcons.Add(Vive_Right_Trackpad_Left);

	FButtonIcon Vive_Right_Trackpad_Right;
	Vive_Right_Trackpad_Right.KeyDisplayName = FText::AsCultureInvariant(("Vive Right Trackpad Right"));
	ButtonIcons.Add(Vive_Right_Trackpad_Right);

	// Microsoft Mixed Reality Motion Controller

	FButtonIcon MixedReality_Left_Menu_Click;
	MixedReality_Left_Menu_Click.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Left Menu Click"));
	ButtonIcons.Add(MixedReality_Left_Menu_Click);

	FButtonIcon MixedReality_Left_Grip_Click;
	MixedReality_Left_Grip_Click.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Left Grip Click"));
	ButtonIcons.Add(MixedReality_Left_Grip_Click);

	FButtonIcon MixedReality_Left_Trigger_Click;
	MixedReality_Left_Trigger_Click.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Left Trigger Click"));
	ButtonIcons.Add(MixedReality_Left_Trigger_Click);

	FButtonIcon MixedReality_Left_Thumbstick_Click;
	MixedReality_Left_Thumbstick_Click.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Left Thumbstick Click"));
	ButtonIcons.Add(MixedReality_Left_Thumbstick_Click);

	FButtonIcon MixedReality_Left_Trackpad_Touch;
	MixedReality_Left_Trackpad_Touch.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Left Trackpad Touch"));
	ButtonIcons.Add(MixedReality_Left_Trackpad_Touch);

	FButtonIcon MixedReality_Left_Trackpad_Up;
	MixedReality_Left_Trackpad_Up.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Left Trackpad Up"));
	ButtonIcons.Add(MixedReality_Left_Trackpad_Up);

	FButtonIcon MixedReality_Left_Trackpad_Down;
	MixedReality_Left_Trackpad_Down.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Left Trackpad Down"));
	ButtonIcons.Add(MixedReality_Left_Trackpad_Down);

	FButtonIcon MixedReality_Left_Trackpad_Left;
	MixedReality_Left_Trackpad_Left.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Left Trackpad Left"));
	ButtonIcons.Add(MixedReality_Left_Trackpad_Left);

	FButtonIcon MixedReality_Left_Trackpad_Right;
	MixedReality_Left_Trackpad_Right.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Left Trackpad Right"));
	ButtonIcons.Add(MixedReality_Left_Trackpad_Right);

	FButtonIcon MixedReality_Right_Menu_Click;
	MixedReality_Right_Menu_Click.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Right Menu Click"));
	ButtonIcons.Add(MixedReality_Right_Menu_Click);

	FButtonIcon MixedReality_Right_Grip_Click;
	MixedReality_Right_Grip_Click.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Right Grip Click"));
	ButtonIcons.Add(MixedReality_Right_Grip_Click);

	FButtonIcon MixedReality_Right_Trigger_Click;
	MixedReality_Right_Trigger_Click.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Right Trigger Click"));
	ButtonIcons.Add(MixedReality_Right_Trigger_Click);

	FButtonIcon MixedReality_Right_Thumbstick_Click;
	MixedReality_Right_Thumbstick_Click.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Right Thumbstick Click"));
	ButtonIcons.Add(MixedReality_Right_Thumbstick_Click);

	FButtonIcon MixedReality_Right_Trackpad_Click;
	MixedReality_Right_Trackpad_Click.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Right Trackpad Click"));
	ButtonIcons.Add(MixedReality_Right_Trackpad_Click);

	FButtonIcon MixedReality_Right_Trackpad_Touch;
	MixedReality_Right_Trackpad_Touch.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Right Trackpad Touch"));
	ButtonIcons.Add(MixedReality_Right_Trackpad_Touch);

	FButtonIcon MixedReality_Right_Trackpad_Up;
	MixedReality_Right_Trackpad_Up.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Right Trackpad Up"));
	ButtonIcons.Add(MixedReality_Right_Trackpad_Up);

	FButtonIcon MixedReality_Right_Trackpad_Down;
	MixedReality_Right_Trackpad_Down.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Right Trackpad Down"));
	ButtonIcons.Add(MixedReality_Right_Trackpad_Down);

	FButtonIcon MixedReality_Right_Trackpad_Left;
	MixedReality_Right_Trackpad_Left.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Right Trackpad Left"));
	ButtonIcons.Add(MixedReality_Right_Trackpad_Left);

	FButtonIcon MixedReality_Right_Trackpad_Right;
	MixedReality_Right_Trackpad_Right.KeyDisplayName = FText::AsCultureInvariant(("MixedReality Right Trackpad Right"));
	ButtonIcons.Add(MixedReality_Right_Trackpad_Right);

	// Oculus Touch Controller
	FButtonIcon OculusTouch_Left_X_Click;
	OculusTouch_Left_X_Click.KeyDisplayName = FText::AsCultureInvariant(("Oculus Touch Left X Click"));
	ButtonIcons.Add(OculusTouch_Left_X_Click);

	FButtonIcon OculusTouch_Left_Y_Click;
	OculusTouch_Left_Y_Click.KeyDisplayName = FText::AsCultureInvariant(("Oculus Touch Left Y Click"));
	ButtonIcons.Add(OculusTouch_Left_Y_Click);

	FButtonIcon OculusTouch_Left_X_Touch;
	OculusTouch_Left_X_Touch.KeyDisplayName = FText::AsCultureInvariant(("Oculus Touch Left X Touch"));
	ButtonIcons.Add(OculusTouch_Left_X_Touch);

	FButtonIcon OculusTouch_Left_Y_Touch;
	OculusTouch_Left_Y_Touch.KeyDisplayName = FText::AsCultureInvariant(("Oculus Touch Left Y Touch"));
	ButtonIcons.Add(OculusTouch_Left_Y_Touch);

	FButtonIcon OculusTouch_Left_Menu_Click;
	OculusTouch_Left_Menu_Click.KeyDisplayName = FText::AsCultureInvariant(("Oculus Touch Left Menu Click"));
	ButtonIcons.Add(OculusTouch_Left_Menu_Click);

	FButtonIcon OculusTouch_Left_Grip_Click;
	OculusTouch_Left_Grip_Click.KeyDisplayName = FText::AsCultureInvariant(("Oculus Touch Left Grip Click"));
	ButtonIcons.Add(OculusTouch_Left_Grip_Click);

	FButtonIcon OculusTouch_Left_Thumbstick_Click;
	OculusTouch_Left_Thumbstick_Click.KeyDisplayName = FText::AsCultureInvariant(("Oculus Touch Left Thumbstick Click"));
	ButtonIcons.Add(OculusTouch_Left_Thumbstick_Click);

	FButtonIcon OculusTouch_Left_Thumbstick_Touch;
	OculusTouch_Left_Thumbstick_Touch.KeyDisplayName = FText::AsCultureInvariant(("Oculus Touch Left Thumbstick Touch"));
	ButtonIcons.Add(OculusTouch_Left_Thumbstick_Touch);

	FButtonIcon OculusTouch_Right_A_Click;
	OculusTouch_Right_A_Click.KeyDisplayName = FText::AsCultureInvariant(("Oculus Touch Right A Click"));
	ButtonIcons.Add(OculusTouch_Right_A_Click);

	FButtonIcon OculusTouch_Right_B_Click;
	OculusTouch_Right_B_Click.KeyDisplayName = FText::AsCultureInvariant(("Oculus Touch Right B Click"));
	ButtonIcons.Add(OculusTouch_Right_B_Click);

	FButtonIcon OculusTouch_Right_A_Touch;
	OculusTouch_Right_A_Touch.KeyDisplayName = FText::AsCultureInvariant(("Oculus Touch Right A Touch"));
	ButtonIcons.Add(OculusTouch_Right_A_Touch);

	FButtonIcon OculusTouch_Right_B_Touch;
	OculusTouch_Right_B_Touch.KeyDisplayName = FText::AsCultureInvariant(("Oculus Touch Right B Touch"));
	ButtonIcons.Add(OculusTouch_Right_B_Touch);

	FButtonIcon OculusTouch_Right_Grip_Click;
	OculusTouch_Right_Grip_Click.KeyDisplayName = FText::AsCultureInvariant(("Oculus Touch Right Grip Click"));
	ButtonIcons.Add(OculusTouch_Right_Grip_Click);

	// Valve Index Controller
	FButtonIcon ValveIndex_Left_A_Click;
	ValveIndex_Left_A_Click.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Left A Click"));
	ButtonIcons.Add(ValveIndex_Left_A_Click);

	FButtonIcon ValveIndex_Left_B_Click;
	ValveIndex_Left_B_Click.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Left B Click"));
	ButtonIcons.Add(ValveIndex_Left_B_Click);

	FButtonIcon ValveIndex_Left_A_Touch;
	ValveIndex_Left_A_Touch.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Left A Touch"));
	ButtonIcons.Add(ValveIndex_Left_A_Touch);

	FButtonIcon ValveIndex_Left_B_Touch;
	ValveIndex_Left_B_Touch.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Left B Touch"));
	ButtonIcons.Add(ValveIndex_Left_B_Touch);

	FButtonIcon ValveIndex_Left_Trigger_Click;
	ValveIndex_Left_Trigger_Click.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Left Trigger Click"));
	ButtonIcons.Add(ValveIndex_Left_Trigger_Click);

	FButtonIcon ValveIndex_Left_Trigger_Touch;
	ValveIndex_Left_Trigger_Touch.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Left Trigger Touch"));
	ButtonIcons.Add(ValveIndex_Left_Trigger_Touch);

	FButtonIcon ValveIndex_Left_Thumbstick_Click;
	ValveIndex_Left_Thumbstick_Click.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Left Thumbstick Click"));
	ButtonIcons.Add(ValveIndex_Left_Thumbstick_Click);

	FButtonIcon ValveIndex_Left_Thumbstick_Touch;
	ValveIndex_Left_Thumbstick_Touch.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Left Thumbstick Touch"));
	ButtonIcons.Add(ValveIndex_Left_Thumbstick_Touch);

	FButtonIcon ValveIndex_Left_Trackpad_Touch;
	ValveIndex_Left_Trackpad_Touch.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Left Trackpad Touch"));
	ButtonIcons.Add(ValveIndex_Left_Trackpad_Touch);

	FButtonIcon ValveIndex_Left_Trackpad_Up;
	ValveIndex_Left_Trackpad_Up.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Left Trackpad Up"));
	ButtonIcons.Add(ValveIndex_Left_Trackpad_Up);

	FButtonIcon ValveIndex_Left_Trackpad_Down;
	ValveIndex_Left_Trackpad_Down.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Left Trackpad Down"));
	ButtonIcons.Add(ValveIndex_Left_Trackpad_Down);

	FButtonIcon ValveIndex_Left_Trackpad_Left;
	ValveIndex_Left_Trackpad_Left.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Left Trackpad Left"));
	ButtonIcons.Add(ValveIndex_Left_Trackpad_Left);

	FButtonIcon ValveIndex_Left_Trackpad_Right;
	ValveIndex_Left_Trackpad_Right.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Left Trackpad Right"));
	ButtonIcons.Add(ValveIndex_Left_Trackpad_Right);

	FButtonIcon ValveIndex_Right_A_Click;
	ValveIndex_Right_A_Click.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Right A Click"));
	ButtonIcons.Add(ValveIndex_Right_A_Click);

	FButtonIcon ValveIndex_Right_B_Click;
	ValveIndex_Right_B_Click.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Right B Click"));
	ButtonIcons.Add(ValveIndex_Right_B_Click);

	FButtonIcon ValveIndex_Right_A_Touch;
	ValveIndex_Right_A_Touch.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Right A Touch"));
	ButtonIcons.Add(ValveIndex_Right_A_Touch);

	FButtonIcon ValveIndex_Right_B_Touch;
	ValveIndex_Right_B_Touch.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Right B Touch"));
	ButtonIcons.Add(ValveIndex_Right_B_Touch);

	FButtonIcon ValveIndex_Right_Trigger_Click;
	ValveIndex_Right_Trigger_Click.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Right Trigger Click"));
	ButtonIcons.Add(ValveIndex_Right_Trigger_Click);

	FButtonIcon ValveIndex_Right_Trigger_Touch;
	ValveIndex_Right_Trigger_Touch.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Right Trigger Touch"));
	ButtonIcons.Add(ValveIndex_Right_Trigger_Touch);

	FButtonIcon ValveIndex_Right_Thumbstick_Click;
	ValveIndex_Right_Thumbstick_Click.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Right Thumbstick Click"));
	ButtonIcons.Add(ValveIndex_Right_Thumbstick_Click);

	FButtonIcon ValveIndex_Right_Thumbstick_Touch;
	ValveIndex_Right_Thumbstick_Touch.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Right Thumbstick Touch"));
	ButtonIcons.Add(ValveIndex_Right_Thumbstick_Touch);

	FButtonIcon ValveIndex_Right_Trackpad_Touch;
	ValveIndex_Right_Trackpad_Touch.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Right Trackpad Touch"));
	ButtonIcons.Add(ValveIndex_Right_Trackpad_Touch);

	FButtonIcon ValveIndex_Right_Trackpad_Up;
	ValveIndex_Right_Trackpad_Up.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Right Trackpad Up"));
	ButtonIcons.Add(ValveIndex_Right_Trackpad_Up);

	FButtonIcon ValveIndex_Right_Trackpad_Down;
	ValveIndex_Right_Trackpad_Down.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Right Trackpad Down"));
	ButtonIcons.Add(ValveIndex_Right_Trackpad_Down);

	FButtonIcon ValveIndex_Right_Trackpad_Left;
	ValveIndex_Right_Trackpad_Left.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Right Trackpad Left"));
	ButtonIcons.Add(ValveIndex_Right_Trackpad_Left);

	FButtonIcon ValveIndex_Right_Trackpad_Right;
	ValveIndex_Right_Trackpad_Right.KeyDisplayName = FText::AsCultureInvariant(("Valve Index Right Trackpad Right"));
	ButtonIcons.Add(ValveIndex_Right_Trackpad_Right);

	for (int i = 0; i < ButtonIcons.Num(); i++)
	{
		if (AICON.Succeeded()) 
		{
			ButtonIcons[i].IcoNormal = AICON.Object;
			ButtonIcons[i].IcoPressed = AICON.Object;
			ButtonIcons[i].IcoHovered = AICON.Object;
			ButtonIcons[i].IcoDisabled = AICON.Object;
		}
	}

	TitleTextColor = FColor(255, 255, 255);
}

void UControlsSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	///Apply
	ApplyButton->OnPressed.Clear();

	ApplyButton->OnPressed.AddDynamic(this, &UControlsSettingsWidget::OnApplyPress);

	if (bInstantApply)
	{
		ApplyButton->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		ApplyButton->SetVisibility(ESlateVisibility::Visible);
	}

	if (!ResetButton->OnPressed.IsAlreadyBound(this, &UControlsSettingsWidget::ResetSettings))
	{
		ResetButton->OnPressed.AddDynamic(this, &UControlsSettingsWidget::ResetSettings);
	}

	LoadInputMappings();
}

void UControlsSettingsWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

}

void UControlsSettingsWidget::UpdateTextBlock()
{
	if (KeyBindingParamLineArr.Num())
	{
		for (int i = 0; i < KeyBindingParamLineArr.Num(); i++)
		{
			KeyBindingParamLineArr[i]->SetTitleTextColor(TitleTextColor);
			KeyBindingParamLineArr[i]->SetTitleTextFont(TitleTextFont);
		}
	}
}

void UControlsSettingsWidget::AddKeyBindingParamLine(int KeyIndex)
{
	if (KeyArray.Num() && KeyArray.IsValidIndex(KeyIndex) && KeyBindingWidgetClass)
	{
		UKeyBindingWidget* KeyBindingParamLine = WidgetTree->ConstructWidget<UKeyBindingWidget>(KeyBindingWidgetClass.Get(), *(FString("KeyBindingParamLine") + FString::FromInt(KeyBindingParamLineArr.Num())));

		if (KeyBindingParamLine)
		{
			FText TitleText;

			TitleText = KeyArray[KeyIndex].GetDisplayName();

			/*Setting Title Text*/
			KeyBindingParamLine->SetTitleText(TitleText);

			KeyBindingParamLine->ButtonIcons = ButtonIcons;

			if (bCustomTitleTextStyle)
			{
				//Set Font
				KeyBindingParamLine->SetTitleTextColor(TitleTextColor);
				KeyBindingParamLine->SetTitleTextFont(TitleTextFont);
			}

			KeyBindingParamLine->KeyBindingType = KeyBindingType;
			KeyBindingParamLine->ButtonIcons = ButtonIcons;

			if (KeyBindingType == EKeyBindingTypes::Text)
			{
				//Key Itself
				KeyBindingParamLine->SetSelectedKey(KeyArray[KeyIndex].Key);
			}
			else
			{
				KeyBindingParamLine->SetSelectedKey(KeyArray[KeyIndex].Key);
				KeyBindingParamLine->UpdateIcon(KeyArray[KeyIndex].Key);
			}

			KeyBindingParamLineArr.Add(KeyBindingParamLine);

			if (const auto RootWidgetSlot = ScrollBox->AddChild(KeyBindingParamLine))
			{
				/*RootWidgetSlot->();
				RootWidgetSlot->SetAnchors(FAnchors(0, 0, 1, 1)); RootWidgetSlot->SetOffsets(FMargin(0, 0));*/
			}
			//WidgetTree->RootWidget = RootWidget;
		}
	}
}

void UControlsSettingsWidget::SetTitleTextColor(FColor Color)
{
	TitleTextColor = Color;

	UpdateTextBlock();
}

void UControlsSettingsWidget::SetTitleTextFont(FSlateFontInfo Font)
{
	TitleTextFont = Font;

	UpdateTextBlock();
}

void UControlsSettingsWidget::SaveInputMappings()
{
	/*if (!IsSettingsSaved())
	{*/
		TSubclassOf<UControlsSave> SaveClass;

		if (ControlsSaveClass)
		{
			SaveClass = ControlsSaveClass;
		}
		else
		{
			SaveClass = UControlsSave::StaticClass();
		}

		UControlsSave* ControlsSave = Cast<UControlsSave>(UGameplayStatics::CreateSaveGameObject(SaveClass));

		if (ControlsSave)
		{
			if (UGameplayStatics::DoesSaveGameExist("Controls", 0))
			{
				ControlsSave = Cast<UControlsSave>(UGameplayStatics::LoadGameFromSlot("Controls", 0));
			}
		}

		if (ControlsSave)
		{
			if (PlayerInputMapping)
			{
				for (int i = 0; i < KeyBindingParamLineArr.Num(); i++)
				{
					for (int j = 0; j < KeyArray.Num(); j++)
					{
						if (KeyBindingParamLineArr[i]->TitleText.ToString() == KeyArray[j].GetDisplayName().ToString())
						{
							PlayerInputMapping->UnmapKey(KeyArray[j].Action, KeyArray[j].Key);
							PlayerInputMapping->MapKey(KeyArray[j].Action, KeyBindingParamLineArr[i]->GetSelectedKey().Key);

							KeyArray[j].Key = KeyBindingParamLineArr[i]->GetSelectedKey().Key;

							break;
						}
					}
				}
			}

			ControlsSave->KeyArray = KeyArray;
			DefaultKeyArray = KeyArray;

			UGameplayStatics::SaveGameToSlot(ControlsSave, "Controls", 0); //Finally saving the stuff to the slot. 
		}
	//}
}

void UControlsSettingsWidget::LoadInputMappings()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);

	if (PC)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

		if (Subsystem)
		{
			DefaultKeyArray = Subsystem->GetAllPlayerMappableActionKeyMappings();
		}
	}

	TSubclassOf<UControlsSave> SaveClass;

	if (ControlsSaveClass)
	{
		SaveClass = ControlsSaveClass;
	}
	else
	{
		SaveClass = UControlsSave::StaticClass();
	}

	UControlsSave* ControlsSave = Cast<UControlsSave>(UGameplayStatics::CreateSaveGameObject(SaveClass));

	if (ControlsSave)
	{
		if (UGameplayStatics::DoesSaveGameExist("Controls", 0))
		{
			ControlsSave = Cast<UControlsSave>(UGameplayStatics::LoadGameFromSlot("Controls", 0));

			if (ControlsSave)
			{
				if (!ControlsSave->KeyArray.IsEmpty())
				{
					KeyArray = ControlsSave->KeyArray;
				}
				else if (!DefaultKeyArray.IsEmpty())
				{
					KeyArray = DefaultKeyArray;
				}
			}
			else
			{
				KeyArray = DefaultKeyArray;
			}
		}
		else if (!DefaultKeyArray.IsEmpty())
		{
			KeyArray = DefaultKeyArray;

			ControlsSave->KeyArray = KeyArray;
		}
	}
	else
	{
		KeyArray = DefaultKeyArray;
	}

	if (!KeyArray.IsEmpty() && !KeyBindingParamLineArr.Num())
	{
		for (int i = 0; i < KeyArray.Num(); i++)
		{
			AddKeyBindingParamLine(i);
		}
	}
}

void UControlsSettingsWidget::ResetSettings()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	TArray<FEnhancedActionKeyMapping> Array;

	TSubclassOf<UControlsSave> SaveClass;

	if (ControlsSaveClass)
	{
		SaveClass = ControlsSaveClass;
	}
	else
	{
		SaveClass = UControlsSave::StaticClass();
	}

	UControlsSave* ControlsSave = Cast<UControlsSave>(UGameplayStatics::CreateSaveGameObject(SaveClass));

	if (ControlsSave)
	{
		Array = ControlsSave->KeyArray;

		if (!Array.IsEmpty() && KeyBindingParamLineArr.Num())
		{
			for (int i = 0; i < KeyBindingParamLineArr.Num(); i++)
			{
				for (int j = 0; j < Array.Num(); j++)
				{
					if (KeyBindingParamLineArr[i]->TitleText.ToString() == Array[j].GetDisplayName().ToString())
					{
						KeyBindingParamLineArr[i]->SetSelectedKey(Array[j].Key);
						break;
					}
				}
			}
		}
	}
}

void UControlsSettingsWidget::OnApplyPress()
{
	SaveInputMappings();
}

void UControlsSettingsWidget::SetDefaultKeyArray(TArray<FEnhancedActionKeyMapping> Array)
{
	DefaultKeyArray = Array;
	KeyArray = DefaultKeyArray;
}

bool UControlsSettingsWidget::IsSettingsSaved()
{
	bool IsSaved = true;

	TSubclassOf<UControlsSave> SaveClass;

	if (ControlsSaveClass)
	{
		SaveClass = ControlsSaveClass;
	}
	else
	{
		SaveClass = UControlsSave::StaticClass();
	}

	UControlsSave* LastControlsSave = Cast<UControlsSave>(UGameplayStatics::CreateSaveGameObject(SaveClass));

	if (LastControlsSave)
	{
		if (UGameplayStatics::DoesSaveGameExist("Controls", 0))
		{
			LastControlsSave = Cast<UControlsSave>(UGameplayStatics::LoadGameFromSlot("Controls", 0));

			if (LastControlsSave)
			{
				for (int i = 0; i < KeyArray.Num(); i++)
				{
					if (KeyBindingParamLineArr.IsValidIndex(i) && LastControlsSave->KeyArray.IsValidIndex(i))
					{
						if (KeyBindingParamLineArr[i]->GetSelectedKey().Key != LastControlsSave->KeyArray[i].Key)
						{
							IsSaved = false;
							break;
						}
					}
				}
			}
		}
	}

	return IsSaved;
}