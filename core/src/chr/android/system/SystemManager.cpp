#include "chr/android/system/SystemManager.h"
#include "chr/cross/Context.h"

#include <sys/system_properties.h>
#include <sys/utsname.h>

using namespace std;

namespace chr
{
  namespace system
  {
    namespace android
    {
      /*
       * XXX: DEPRECATED, STARTING FROM ANDROID LOLLIPOP
       */
      const string getProperty(const char *name)
      {
        static char tmp[256];
        auto len = __system_property_get(name, tmp);
        
        return string(tmp, len);
      }
    }

    // ---
    
    void Manager::setup(const InitInfo &initInfo)
    {
      updateInfo();
      
      LOGI << "SYSTEM INFO: " << info << endl; // LOG: VERBOSE
    }

    fs::path Manager::getDocumentsFolder()
    {
      auto documentsFolder = fs::path(chr::android::externalDataPath) / "Documents";

      if (!boost::filesystem::exists(documentsFolder))
      {
        boost::filesystem::create_directory(documentsFolder);
      }

      return documentsFolder;
    }

    // ---
    
    void Manager::updateInfo()
    {
      /*
       * XXX: ORDER OF EXECUTION MATTERS!
       */
      
      info.model = getModel();
      info.manufacturer = getManufacturer();
      
      ManagerBase::updateInfo();
    }
    
    array<int, 3> Manager::getOsVersion()
    {
      auto releaseString = android::getProperty("ro.build.version.release");
      auto components = utils::split(releaseString, '.');
      
      int major = (components.size() > 0) ? atoi(components[0].data()) : 0;
      int minor = (components.size() > 1) ? atoi(components[1].data()) : 0;
      int patch = (components.size() > 2) ? atoi(components[2].data()) : 0;
      
      return {major, minor, patch};
    }
    
    string Manager::getOsVersionString()
    {
      auto releaseString = android::getProperty("ro.build.version.release");
      auto sdkVersion = getSdkVersion();
      
      if (sdkVersion)
      {
        return releaseString + " [" + utils::toString(sdkVersion) + "]";
      }
      else
      {
        releaseString;
      }
    }
    
    string Manager::getDeviceString()
    {
      return info.model + " [" + info.manufacturer + "]";
    }
    
    int Manager::getSdkVersion()
    {
      auto sdkString = android::getProperty("ro.build.version.sdk");
      return sdkString.empty() ? 0 : atoi(sdkString.data());
    }

    string Manager::getModel()
    {
      return android::getProperty("ro.product.model");
    }
    
    string Manager::getManufacturer()
    {
      return android::getProperty("ro.product.manufacturer");
    }
  }
}
