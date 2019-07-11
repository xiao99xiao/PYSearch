//
//  GitHub: https://github.com/iphone5solo/PYSearch
//  Created by CoderKo1o.
//  Copyright © 2016 iphone5solo. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PYSearchConst.h"

@class PYSearchViewController, PYSearchSuggestionViewController;

typedef void(^PYDidSearchBlock)(PYSearchViewController * _Nonnull searchViewController, UISearchBar * _Nonnull searchBar, NSString * _Nullable searchText);

/**
 style of popular search
 */
typedef NS_ENUM(NSInteger, PYHotSearchStyle)  {
    PYHotSearchStyleNormalTag,      // normal tag without border
    PYHotSearchStyleColorfulTag,    // colorful tag without border, color of background is randrom and can be custom by `colorPol`
    PYHotSearchStyleBorderTag,      // border tag, color of background is `clearColor`
    PYHotSearchStyleARCBorderTag,   // broder tag with ARC, color of background is `clearColor`
    PYHotSearchStyleRankTag,        // rank tag, color of background can be custom by `rankTagBackgroundColorHexStrings`
    PYHotSearchStyleRectangleTag,   // rectangle tag, color of background is `clearColor`
    PYHotSearchStyleDefault = PYHotSearchStyleNormalTag // default is `PYHotSearchStyleNormalTag`
};

/**
 style of search history
 */
typedef NS_ENUM(NSInteger, PYSearchHistoryStyle) {
    PYSearchHistoryStyleCell,           // style of UITableViewCell
    PYSearchHistoryStyleNormalTag,      // style of PYHotSearchStyleNormalTag
    PYSearchHistoryStyleColorfulTag,    // style of PYHotSearchStyleColorfulTag
    PYSearchHistoryStyleBorderTag,      // style of PYHotSearchStyleBorderTag
    PYSearchHistoryStyleARCBorderTag,   // style of PYHotSearchStyleARCBorderTag
    PYSearchHistoryStyleDefault = PYSearchHistoryStyleCell // default is `PYSearchHistoryStyleCell`
};

/**
 mode of search result view controller display
 */
typedef NS_ENUM(NSInteger, PYSearchResultShowMode) {
    PYSearchResultShowModeCustom,   // custom, can be push or pop and so on.
    PYSearchResultShowModePush,     // push, dispaly the view of search result by push
    PYSearchResultShowModeEmbed,    // embed, dispaly the view of search result by embed
    PYSearchResultShowModeDefault = PYSearchResultShowModeCustom // defualt is `PYSearchResultShowModeCustom`
};
/**
 mode of search view controller display
 */
typedef NS_ENUM(NSInteger, PYSearchViewControllerShowMode) {
    PYSearchViewControllerShowModeModal,    // modal, dispaly the view of searchViewController by modal
    PYSearchViewControllerShowModePush,   // push, dispaly the view of searchViewController by push
    PYSearchViewControllerShowDefault = PYSearchViewControllerShowModeModal // defualt is `PYSearchViewControllerShowModeModal`
};


/**
 The protocol of data source, you can custom the suggestion view by implement these methods the data scource.
 */
@protocol PYSearchViewControllerDataSource <NSObject>

@optional

/**
 Return a `UITableViewCell` object.

 @param searchSuggestionView    view which display search suggestions
 @param indexPath               indexPath of row
 @return a `UITableViewCell` object
 */
- (UITableViewCell *_Nullable)searchSuggestionView:(UITableView *_Nonnull)searchSuggestionView cellForRowAtIndexPath:(NSIndexPath *_Nonnull)indexPath;

/**
 Return number of rows in section.

 @param searchSuggestionView    view which display search suggestions
 @param section                 index of section
 @return number of rows in section
 */
- (NSInteger)searchSuggestionView:(UITableView *_Nonnull)searchSuggestionView numberOfRowsInSection:(NSInteger)section;

/**
 Return number of sections in search suggestion view.

 @param searchSuggestionView    view which display search suggestions
 @return number of sections
 */
- (NSInteger)numberOfSectionsInSearchSuggestionView:(UITableView *_Nonnull)searchSuggestionView;

/**
 Return height for row.

 @param searchSuggestionView    view which display search suggestions
 @param indexPath               indexPath of row
 @return height of row
 */
- (CGFloat)searchSuggestionView:(UITableView *_Nonnull)searchSuggestionView heightForRowAtIndexPath:(NSIndexPath *_Nonnull)indexPath;

@end


/**
 The protocol of delegate
 */
@protocol PYSearchViewControllerDelegate <NSObject, UITableViewDelegate>

@optional

/**
 Called when search begain.

 @param searchViewController    search view controller
 @param searchBar               search bar
 @param searchText              text for search
 */
- (void)searchViewController:(PYSearchViewController *_Nonnull)searchViewController
      didSearchWithSearchBar:(UISearchBar *_Nonnull)searchBar
                  searchText:(NSString *_Nullable)searchText;

/**
 Called when popular search is selected.

 @param searchViewController    search view controller
 @param index                   index of tag
 @param searchText              text for search
 
 Note: `searchViewController:didSearchWithSearchBar:searchText:` will not be called when this method is implemented.
 */
- (void)searchViewController:(PYSearchViewController *_Nonnull)searchViewController
   didSelectHotSearchAtIndex:(NSInteger)index
                  searchText:(NSString *_Nullable)searchText;

/**
 Called when search history is selected.

 @param searchViewController    search view controller
 @param index                   index of tag or row
 @param searchText              text for search
 
 Note: `searchViewController:didSearchWithSearchBar:searchText:` will not be called when this method is implemented.
 */
- (void)searchViewController:(PYSearchViewController *_Nonnull)searchViewController
didSelectSearchHistoryAtIndex:(NSInteger)index
                  searchText:(NSString *_Nullable)searchText;

/**
 Called when search suggestion is selected.

 @param searchViewController    search view controller
 @param index                   index of row
 @param searchText              text for search

 Note: `searchViewController:didSearchWithSearchBar:searchText:` will not be called when this method is implemented.
 */
- (void)searchViewController:(PYSearchViewController *_Nonnull)searchViewController
didSelectSearchSuggestionAtIndex:(NSInteger)index
                  searchText:(NSString *_Nullable)searchText PYSEARCH_DEPRECATED("Use searchViewController:didSelectSearchSuggestionAtIndexPath:searchText:");

/**
 Called when search suggestion is selected, the method support more custom of search suggestion view.

 @param searchViewController    search view controller
 @param indexPath               indexPath of row
 @param searchBar               search bar
 
 Note: `searchViewController:didSearchWithSearchBar:searchText:` and `searchViewController:didSelectSearchSuggestionAtIndex:searchText:` will not be called when this method is implemented.
 Suggestion: To ensure that can cache selected custom search suggestion records, you need to set `searchBar.text` = "custom search text".
 */
- (void)searchViewController:(PYSearchViewController *_Nonnull)searchViewController didSelectSearchSuggestionAtIndexPath:(NSIndexPath *_Nonnull)indexPath
                   searchBar:(UISearchBar *_Nonnull)searchBar;

/**
 Called when search text did change, you can reload data of suggestion view thought this method.

 @param searchViewController    search view controller
 @param searchBar               search bar
 @param searchText              text for search
 */
- (void)searchViewController:(PYSearchViewController *_Nonnull)searchViewController
         searchTextDidChange:(UISearchBar *_Nonnull)searchBar
                  searchText:(NSString *_Nullable)searchText;

/**
 Called when cancel item did press, default execute `[self dismissViewControllerAnimated:YES completion:nil]`.

 @param searchViewController search view controller
 */
- (void)didClickCancel:(PYSearchViewController *_Nonnull)searchViewController;

/**
 Called when back item did press, default execute `[self.navigationController popViewControllerAnimated:YES]`.
 
 @param searchViewController search view controller
 */
- (void)didClickBack:(PYSearchViewController *_Nonnull)searchViewController;

@end

@interface PYSearchViewController : UIViewController

/**
 The delegate
 */
@property (nullable, nonatomic, weak) id<PYSearchViewControllerDelegate> delegate;

/**
 The data source
 */
@property (nullable, nonatomic, weak) id<PYSearchViewControllerDataSource> dataSource;

/**
 The text color
 */
@property (nullable, nonatomic, copy) UIColor * textColor;

/**
 The title color
 */
@property (nullable, nonatomic, copy) UIColor * titleColor;

/**
 Ranking the background color of the corresponding hexadecimal string (eg: @"#ffcc99") array (just four colors) when `hotSearchStyle` is `PYHotSearchStyleRankTag`.
 */
@property (nullable, nonatomic, strong) NSArray<NSString *> * rankTagBackgroundColorHexStrings;

/**
 The pool of color which are use in colorful tag when `hotSearchStyle` is `PYHotSearchStyleColorfulTag`.
 */
@property (nullable, nonatomic, strong) NSMutableArray<UIColor *> * colorPol;

/**
 Whether swap the popular search and search history location, default is NO.
 
 Note: It is‘t effective when `searchHistoryStyle` is `PYSearchHistoryStyleCell`.
 */
@property (nonatomic, assign) BOOL swapHotSeachWithSearchHistory;

/**
 The element of popular search
 */
@property (nullable, nonatomic, copy) NSArray<NSString *> * hotSearches;

/**
 The tags of popular search
 */
@property (nullable, nonatomic, copy) NSArray<UILabel *> * hotSearchTags;

/**
 The label of popular search header
 */
@property (nullable, nonatomic, weak) UILabel * hotSearchHeader;

/**
 Whether show popular search, default is YES.
 */
@property (nonatomic, assign) BOOL showHotSearch;

/**
 The title of popular search
 */
@property (nullable, nonatomic, copy) NSString * hotSearchTitle;

/**
 The tags of search history
 */
@property (nullable, nonatomic, copy) NSArray<UILabel *> * searchHistoryTags;

/**
 The label of search history header
 */
@property (nullable, nonatomic, weak) UILabel * searchHistoryHeader;

/**
 The title of search history
 */
@property (nullable, nonatomic, copy) NSString * searchHistoryTitle;

/**
 The color of icons in search history
 */
@property (nullable, nonatomic, copy) UIColor * searchHistoryIconColor;

/**
 The color of seperator lines in search history
 */
@property (nullable, nonatomic, copy) UIColor * searchHistorySeperatorColor;

/**
 Whether show search history, default is YES.
 
 Note: search record is not cache when it is NO.
 */
@property (nonatomic, assign) BOOL showSearchHistory;

/**
 The path of cache search record, default is `PYSEARCH_SEARCH_HISTORY_CACHE_PATH`.
 */
@property (nonnull, nonatomic, copy) NSString * searchHistoriesCachePath;

/**
 The number of cache search record, default is 20.
 */
@property (nonatomic, assign) NSUInteger searchHistoriesCount;

/**
 Whether remove the space of search string, default is YES.
 */
@property (nonatomic, assign) BOOL removeSpaceOnSearchString;

/**
 The button of empty search record when `searchHistoryStyle` is’t `PYSearchHistoryStyleCell`.
 */
@property (nullable, nonatomic, weak) UIButton * emptyButton;

/**
 The label od empty search record when `searchHistoryStyle` is `PYSearchHistoryStyleCell`.
 */
@property (nullable, nonatomic, weak) UILabel * emptySearchHistoryLabel;

/**
 The style of popular search, default is `PYHotSearchStyleNormalTag`.
 */
@property (nonatomic, assign) PYHotSearchStyle hotSearchStyle;

/**
 The style of search histrory, default is `PYSearchHistoryStyleCell`.
 */
@property (nonatomic, assign) PYSearchHistoryStyle searchHistoryStyle;

/**
 The mode of display search result view controller, default is `PYSearchResultShowModeCustom`.
 */
@property (nonatomic, assign) PYSearchResultShowMode searchResultShowMode;

/**
 The mode of display search view controller, default is `PYSearchViewControllerShowModeModal`.
 */
@property (nonatomic, assign) PYSearchViewControllerShowMode searchViewControllerShowMode;

/**
 The search bar
 */
@property (nullable, nonatomic, weak) UISearchBar * searchBar;

/**
 The text field of search bar
 */
@property (nullable, nonatomic, weak) UITextField *searchTextField;

/**
 The background color of search bar.
 */
@property (nullable, nonatomic, strong) UIColor *searchBarBackgroundColor;

/**
 The cornerRadius of `_UISearchBarSearchFieldBackgroundView` which from `self.searchTextField.subviews`, default is 0.0.
 */
@property (nonatomic, assign) CGFloat searchBarCornerRadius;

/**
 The barButtonItem of cancel
 */
@property (nonnull, nonatomic, strong) UIBarButtonItem *cancelBarButtonItem;

/**
 The customView of cancelBarButtonItem
 */
@property (nullable, nonatomic, weak) UIButton *cancelButton;

/**
 The barButtonItem of back
 */
@property (nonnull, nonatomic, strong) UIBarButtonItem *backBarButtonItem;

/**
 The customView of backBarButtonItem
 */
@property (nullable, nonatomic, weak) UIButton *backButton;

/**
 The search suggestion view
 */
@property (nullable, nonatomic, weak, readonly) UITableView *searchSuggestionView;

/**
 The block which invoked when search begain.
 */
@property (nullable, nonatomic, copy) PYDidSearchBlock didSearchBlock;

/**
 The element of search suggestions
 
 Note: it is't effective when `searchSuggestionHidden` is NO or cell of suggestion view is custom.
 */
@property (nullable, nonatomic, copy) NSArray<NSString *> *searchSuggestions;

/**
 Whether hidden search suggstion view, default is NO.
 */
@property (nonatomic, assign) BOOL searchSuggestionHidden;

/**
 The view controller of search result.
 */
@property (nullable, nonatomic, strong) UIViewController *searchResultController;

/**
 Whether show search result view when search text did change, default is NO.
 
 Note: it is effective only when `searchResultShowMode` is `PYSearchResultShowModeEmbed`.
 */
@property (nonatomic, assign) BOOL showSearchResultWhenSearchTextChanged;

/**
 Whether show search result view when search bar become first responder again.
 
 Note: it is effective only when `searchResultShowMode` is `PYSearchResultShowModeEmbed`.
 */
@property (nonatomic, assign) BOOL showSearchResultWhenSearchBarRefocused;

/**
 Whether show keyboard when return to search result, default is YES.
 */
@property (nonatomic, assign) BOOL showKeyboardWhenReturnSearchResult;

/**
 Creates an instance of searchViewContoller with popular searches and search bar's placeholder.

 @param hotSearches     popular searchs
 @param placeholder     placeholder of search bar
 @return new instance of `PYSearchViewController` class
 */
+ (instancetype _Nonnull )searchViewControllerWithHotSearches:(NSArray<NSString *> *_Nonnull)hotSearches
                                         searchBarPlaceholder:(NSString *_Nullable)placeholder;

/**
 Creates an instance of searchViewContoller with popular searches, search bar's placeholder and the block which invoked when search begain.

 @param hotSearches     popular searchs
 @param placeholder     placeholder of search bar
 @param block           block which invoked when search begain
 @return new instance of `PYSearchViewController` class
 
 Note: The `delegate` has a priority greater than the `block`, `block` is't effective when `searchViewController:didSearchWithSearchBar:searchText:` is implemented.
 */
+ (instancetype _Nonnull )searchViewControllerWithHotSearches:(NSArray<NSString *> *_Nonnull)hotSearches
                               searchBarPlaceholder:(NSString *_Nullable)placeholder
                                               didSearchBlock:(PYDidSearchBlock _Nullable )block;

@end
