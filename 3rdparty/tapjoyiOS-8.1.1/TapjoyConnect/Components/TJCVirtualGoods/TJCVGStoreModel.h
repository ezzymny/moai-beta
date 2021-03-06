//Copyright (C) 2011 by Tapjoy Inc.
//
//This file is part of the Tapjoy SDK.
//
//By using the Tapjoy SDK in your software, you agree to the terms of the Tapjoy SDK License Agreement.
//
//The Tapjoy SDK is bound by the Tapjoy SDK License Agreement and can be found here: https://www.tapjoy.com/sdk/license


#import <UIKit/UIKit.h>
#import "TBXML.h"

@class TJCVGStoreItem;
@class TJCVGItemPurchaseResponse;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TJCVGStoreModel
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface TJCVGStoreModel :NSObject
{
	
	NSMutableArray *allItems_; //array of TJCVGStoreItem objects
	NSMutableArray *purchasedItems_; //array of TJCVGStoreItem objects
	NSMutableArray *localItems_; //array of TJCVGStoreItem objects
	
	TJCVGItemPurchaseResponse *buyitemResponse_;
}

//These properties must not be set from outside
@property (nonatomic,readonly) NSMutableArray *allItems;
@property (nonatomic,readonly) NSMutableArray *purchasedItems;
@property (nonatomic,readonly) NSMutableArray *localItems;

- (void) addObjectForAllItems:(TJCVGStoreItem *)vgStoreItem;
- (void) addObjectForPurchasedItems:(TJCVGStoreItem *)vgStoreItem;
- (void) setBuyItemResponse:(TJCVGItemPurchaseResponse *)buyitemResponse; //my own setter does perform the retain
- (TJCVGItemPurchaseResponse *) getBuyItemResponse;
- (void) releasePurchasedItems;
- (void)releaseAllItems;
- (void) releaseBuyItemReponse;

@end







////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TJCVGStoreItem
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface TJCVGStoreItem : NSObject
{
	NSMutableArray * itemAttributes_;
	
	NSString *itemID_;
	NSString *itemName_;
	NSString *itemDescription_;
	NSString *itemAppleProductID_;
	NSString *itemTypeName_;
	NSString *itemDatafileURL_;
	NSString *itemThumbImageURL_;
	NSString *itemFullImageURL_;
	NSString *itemCurrencyName_;
	NSString *itemDataHash_;
	
	UIImage *itemThumbNailImage_;
	
	long int itemPrice_;
	int itemNumberOwned_;
	
	NSString *itemDataFileDirPath_;
	NSString *itemThumbImageFilePath_;
	NSString *itemFullImageFilePath_;
}

@property (nonatomic,readonly) NSMutableArray *itemAttributes;
@property (nonatomic,copy) NSString *itemID;
@property (nonatomic,copy) NSString *itemName;
@property (nonatomic,copy) NSString *itemDescription;
@property (nonatomic,copy) NSString *itemTypeName;
@property (nonatomic,copy) NSString *itemAppleProductID;
@property (nonatomic,copy) NSString *itemDatafileURL;
@property (nonatomic,copy) NSString *itemThumbImageURL;
@property (nonatomic,copy) NSString *itemFullImageURL;
@property (nonatomic,copy) NSString *itemCurrencyName;
@property (nonatomic,copy) NSString *itemDataHash;

@property (nonatomic,retain) UIImage *itemThumbNailImage;

@property (nonatomic) long int itemPrice;
@property (nonatomic) int itemNumberOwned;

@property (nonatomic,retain) NSString *itemDataFileDirPath;
@property (nonatomic,retain) NSString *itemThumbImageFilePath;
@property (nonatomic,retain) NSString *itemFullImageFilePath;

- (id)initWithXMLElement:(TBXMLElement *)xmlElementObj;

@end







////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TJCVGStoreItemAttribute
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface TJCVGStoreItemAttribute :NSObject
{
	NSString * attributeType_;
	NSString * attributeValue_;
}

@property(nonatomic,retain) NSString *attributeType;
@property(nonatomic,retain) NSString *attributeValue;

-(id)initWithXMLElement:(TBXMLElement *)xmlElementObj;

@end







////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TJCVGItemPurchaseResponse
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface TJCVGItemPurchaseResponse : NSObject
{
	NSString *message_;
	BOOL success_;
}

@property (nonatomic,retain) NSString *message;
@property BOOL success;

@end







////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StoreItem
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface StoreItem : NSObject
{
	NSString *storeItemID_;
	NSString *appleProductID_;
	NSString *storeItemType_;
	// Item name
	NSString *title_;
	NSString *description_;
	NSString *thumbImageFilePath_;
	NSString *fullImageFilePath_;
	NSString *datafileLocation_;
	NSString *currencyName_;
	NSMutableDictionary *attributeValues_;
	UIImage *thumbImage_;
	UIImage *fullImage_;
	int price_;
}

- (id)initWithObject:(TJCVGStoreItem*)localObj;


/**
 * Returns store item ID
 */
- (NSString*) getStoreItemID;

/**
 * Returns apple product ID
 */
- (NSString*) getAppleProductID;

/**
 * Returns the title of the store item type
 */
- (NSString*) getStoreItemType;

/**
 * Returns the item price
 */
- (int) getPrice;

/**
 * Returns the Currency Name Against which the Item was purchased
 */
- (NSString*) getCurrencyName;
/**
 * Returns store item title
 */
- (NSString*) getTitle;

/**
 * Returns item description
 */
- (NSString*) getDescription;

/**
 * Returns a map with attribute types for keys and attribute values for values (ie. {AttributeType1 => AttributeValue1, ...})
 */
- (NSMutableDictionary*) getAttributeValues;

/**
 * Returns thumb image
 */
- (UIImage*) getThumbImage;

/**
 * Returns large image
 */
- (UIImage*) getFullImage;

/**
 * Returns the path to where the data zip file has been uncompressed
 */
- (NSString*) getDatafileLocation;

@end

