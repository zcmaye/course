# 运行时插件

运行时插件专注于在应用程序运行时动态加载功能模块，主程序只定义接口，插件负责实现具体逻辑，实现核心功能与扩展功能的解耦。

## 核心步骤

### 1. 定义插件接口

在应用程序项目中，创建一个抽象基类（如`ToolInterface`），声明一些纯虚函数作为插件必须实现的接口，例如`widget()`、`name()`等。

```cpp
#pragma once

#include <QtPlugin>

/**
 * 工具接口.
 */
class ToolInterface
{
public:
	ToolInterface() {}
	virtual ~ToolInterface() {}

	/*!工具名*/
	virtual QString name() const = 0;
	/*!工具类别名*/
	virtual QString category() const = 0;
	/*!工具图标*/
	virtual QIcon icon() const = 0;
	/*!工具描述*/
	virtual QString description() const = 0;
	/*!工具的控件对象*/
	virtual QWidget* widget() = 0;
};

Q_DECLARE_INTERFACE(ToolInterface, "com.maye.ToolInterface/1.0")
```

### 2. 创建插件项目

使用CMake作为构建工具，CMakeLists.txt文件内容如下：

```cpp
cmake_minimum_required(VERSION 3.16)
project(base_one LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Widgets
)

qt_standard_project_setup()

set(PLUGIN_SOURCES
    plugins/TestToolPlugin.h
    plugins/TestToolPlugin.cpp
)

add_library(TestToolPlugin SHARED ${PLUGIN_SOURCES})

target_link_libraries(TestToolPlugin Qt::Core Qt::Widgets)
```

### 3. 实现插件

创建一个同时继承自`QWidget`（或其子类）和接口类（如`ToolInterface`）的类（必须先继承QWidget）。在类实现中，必须使用`Q_INTERFACES`宏声明所实现的接口，并使用`Q_PLUGIN_METADATA`宏导出插件。

TestToolPlugin.h

```cpp
#include <QWidget>

class TestToolPlugin : public QWidget, public ToolInterface
{
	Q_OBJECT
	Q_INTERFACES(ToolInterface)
    Q_PLUGIN_METADATA(IID "com.maye.ToolInterface/1.0")
public:
	TestToolPlugin(QWidget* parent = nullptr);

	QString name() const override;

	QString category() const override;

	QIcon icon() const override;

	QString description() const override;

	QWidget* widget() override;

};
```

TestToolPlugin.cpp

```cpp
#include "TestToolPlugin.h"
#include <QStyle>
#include <QPushButton>
#include <QMessageBox>

TestToolPlugin::TestToolPlugin(QWidget* parent)
	: QWidget(parent)
{
	auto btn = new QPushButton(this);

	connect(btn, &QPushButton::clicked, this, [this] {
		QMessageBox::information(this, "测试插件", "这是一个测试插件");
		});
}

QString TestToolPlugin::name() const
{
	return "测试插件";
}

QString TestToolPlugin::category() const
{
	return "热门工具";
}

QIcon TestToolPlugin::icon() const
{
	return QIcon(style()->standardPixmap(QStyle::SP_MessageBoxInformation));
}

QString TestToolPlugin::description() const
{
	return QString("创建一个同时继承自QWidget（或其子类）和接口类（如ToolInterface）的类。在类实现中，必须使用Q_INTERFACES宏声明所实现的接口，并使用Q_PLUGIN_METADATA宏导出插件");
}

QWidget* TestToolPlugin::widget()
{
	return this;
}
```

### 4. 在主程序中加载插件

在主程序中使用`QPluginLoader`，指向插件库的路径并加载。

```cpp
#include <QApplication>
#include "plugins/ToolInterface.h"
#include <QPluginLoader>

class Test {
public:
	Test() {
		test();
	}
	~Test() {
		m_loader->unload();
	}

	void test() {
		m_loader = new QPluginLoader("F:/MyCode/qt/tools/tools/out/build/debug/TestToolPlugin.dll");

		ToolInterface* tool = qobject_cast<ToolInterface*>(m_loader->instance());
		if (tool) {
			qDebug() << "Plugin loaded successfully";
			qDebug() << tool->name() << tool->description() << tool->category();

			if (auto w = tool->widget()) {
				w->show();
			}
		}

	}
	QPluginLoader* m_loader;
};


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Test t;

	return app.exec();
}
```

`instance`函数用于返回插件的根组件对象。如果需要，会加载插件。如果插件无法加载或无法实例化根组件对象，则该函数返回 nullptr。

如果根组件对象已被销毁，调用此函数将创建一个新实例。

此函数返回的根组件在 QPluginLoader 被销毁时不会被删除。如果您希望确保根组件被删除，应在不再需要访问核心组件时尽快调用 `unload()`。当库最终被卸载时，根组件将自动被删除。

组件对象是一个 QObject。使用 qobject_cast() 来访问您感兴趣的接口。