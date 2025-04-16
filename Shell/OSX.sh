#释放hidden space
sudo tmutil disablelocal
sudo tmutil enablelocal

# Xcode插件相关
## AlInstaz install
curl -fsSL https://raw.github.com/supermarin/Alcatraz/master/Scripts/install.sh | sh
## Uninstall
rm -rf ~/Library/Application\ Support/Developer/Shared/Xcode/Plug-ins/Alcatraz.xcplugin
# 所有Alcatraz安装的插件
rm -rf ~/Library/Application\ Support/Alcatraz/

# 更新后Xcode插件失效
find ~/Library/Application\ Support/Developer/Shared/Xcode/Plug-ins -name Info.plist -maxdepth 3 | xargs -I{} defaults write {} DVTPlugInCompatibilityUUIDs -array-add `defaults read /Applications/Xcode.app/Contents/Info DVTPlugInCompatibilityUUID`
sudo xcode-select --reset

#清理DNS缓存
sudo discoveryutil mdnsflushcache

#禁用仪表盘
defaults write com.apple.dashboard mcx-disabled -boolean YES && killall Dock
打开：defaults write com.apple.dashboard mcx-disabled -boolean NO && killall Dock

#显示隐藏文件
defaults write com.apple.finder AppleShowAllFiles -bool true
defaults write com.apple.finder AppleShowAllFiles -bool false

#重启Quick Look(用于安装插件后)
qlmanage -r

#purge命令可以清除内存和硬盘的缓存，与重启Mac的效果差不多。purge命令可以让不活跃的系统内存转变为可以使用的内存
purge

#打开任意来源app
sudo spctl --master-disable

#使用pkgutil解压PKG文件
pkgutil --expand macx.pkg /Desktop/

#查找
mdfind -onlyin ./ "ab" | xargs grep "ab"

#删除Mac生成的隐藏文件
find . -name “._*” -type f -delete
find . -name .DS_Store -type f -delete