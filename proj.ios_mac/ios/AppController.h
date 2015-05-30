#import <UIKit/UIKit.h>
#import <CoreBluetooth/CoreBluetooth.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate, CBPeripheralDelegate, CBCentralManagerDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;

- (void)scanBluetoothDevice:(bool)start;

@end

