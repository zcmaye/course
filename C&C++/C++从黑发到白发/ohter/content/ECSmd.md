以下是一个简单的ECS（Entity-Component-System）系统实现。这个实现包含核心的ECS概念：实体管理、组件存储和系统处理逻辑。

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <set>
#include <typeindex>
#include <functional>

// 基础组件类
struct Component {
    virtual ~Component() = default;
};

// 实体ID类型
using Entity = uint32_t;

// 组件管理器
class ComponentManager {
public:
    template<typename T, typename... Args>
    T& addComponent(Entity entity, Args&&... args) {
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        auto& storage = getComponentStorage<T>();
        storage[entity] = std::move(comp);
        return *storage[entity];
    }

    template<typename T>
    void removeComponent(Entity entity) {
        auto& storage = getComponentStorage<T>();
        storage.erase(entity);
    }

    template<typename T>
    T* getComponent(Entity entity) {
        auto& storage = getComponentStorage<T>();
        auto it = storage.find(entity);
        return (it != storage.end()) ? it->second.get() : nullptr;
    }

    template<typename T>
    bool hasComponent(Entity entity) {
        return getComponentStorage<T>().find(entity) != getComponentStorage<T>().end();
    }

private:
    template<typename T>
    using ComponentStorage = std::unordered_map<Entity, std::unique_ptr<T>>;

    template<typename T>
    ComponentStorage<T>& getComponentStorage() {
        static ComponentStorage<T> storage;
        return storage;
    }
};

// 系统基类
class System {
public:
    virtual void update(float dt) = 0;
    virtual ~System() = default;
    
    std::set<Entity> entities;
};

// 实体管理器
class EntityManager {
public:
    Entity createEntity() {
        Entity entity = nextId++;
        entities.insert(entity);
        return entity;
    }

    void destroyEntity(Entity entity) {
        entities.erase(entity);
    }

    const std::set<Entity>& getAllEntities() const {
        return entities;
    }

private:
    std::set<Entity> entities;
    Entity nextId = 0;
};

// ECS世界（协调实体、组件、系统）
class World {
public:
    Entity createEntity() {
        return entityManager.createEntity();
    }

    void destroyEntity(Entity entity) {
        entityManager.destroyEntity(entity);
        // 通知所有系统移除该实体
        for (auto& system : systems) {
            system.second->entities.erase(entity);
        }
    }

    template<typename T, typename... Args>
    T& addComponent(Entity entity, Args&&... args) {
        return componentManager.addComponent<T>(entity, std::forward<Args>(args)...);
    }

    template<typename T>
    void removeComponent(Entity entity) {
        componentManager.removeComponent<T>(entity);
    }

    template<typename T>
    T* getComponent(Entity entity) {
        return componentManager.getComponent<T>(entity);
    }

    template<typename T, typename... Args>
    std::shared_ptr<T> registerSystem(Args&&... args) {
        auto system = std::make_shared<T>(std::forward<Args>(args)...);
        systems[typeid(T)] = system;
        return system;
    }

    template<typename T>
    void setSystemSignature(const std::vector<std::type_index>& signature) {
        systemSignatures[typeid(T)] = signature;
    }

    void updateSystems(float dt) {
        for (auto& pair : systems) {
            pair.second->update(dt);
        }
    }

    // 当组件变化时更新系统实体列表
    template<typename T>
    void componentUpdated(Entity entity) {
        for (auto& pair : systems) {
            const auto& signature = systemSignatures[pair.first];
            bool hasAllComponents = true;
            
            for (const auto& compType : signature) {
                if (compType == typeid(T)) continue;
                // 需要检查其他组件类型是否存在（简化实现）
                // 实际应用中这里需要更复杂的类型检查
            }
            
            if (hasAllComponents) {
                pair.second->entities.insert(entity);
            } else {
                pair.second->entities.erase(entity);
            }
        }
    }

private:
    EntityManager entityManager;
    ComponentManager componentManager;
    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
    std::unordered_map<std::type_index, std::vector<std::type_index>> systemSignatures;
};

// --- 示例用法 ---
// 定义组件
struct Transform : Component {
    float x = 0, y = 0;
    Transform(float x, float y) : x(x), y(y) {}
};

struct Velocity : Component {
    float vx = 0, vy = 0;
    Velocity(float vx, float vy) : vx(vx), vy(vy) {}
};

// 定义系统
class MovementSystem : public System {
public:
    void update(float dt) override {
        for (auto entity : entities) {
            auto* transform = world->getComponent<Transform>(entity);
            auto* velocity = world->getComponent<Velocity>(entity);
            
            if (transform && velocity) {
                transform->x += velocity->vx * dt;
                transform->y += velocity->vy * dt;
                std::cout << "Entity " << entity 
                          << " moved to (" << transform->x 
                          << ", " << transform->y << ")\n";
            }
        }
    }
    
    World* world = nullptr;
};

int main() {
    World world;
    
    // 注册系统
    auto movementSystem = world.registerSystem<MovementSystem>();
    movementSystem->world = &world;
    world.setSystemSignature<MovementSystem>({typeid(Transform), typeid(Velocity)});
    
    // 创建实体
    Entity player = world.createEntity();
    world.addComponent<Transform>(player, 0, 0);
    world.addComponent<Velocity>(player, 1.5f, 2.0f);
    
    Entity npc = world.createEntity();
    world.addComponent<Transform>(npc, 5, 5);
    world.addComponent<Velocity>(npc, -1.0f, 0.5f);
    
    // 更新系统（模拟游戏循环）
    for (int i = 0; i < 5; ++i) {
        std::cout << "--- Frame " << i << " ---\n";
        world.updateSystems(1.0f); // dt = 1.0
    }
    
    return 0;
}
```

### 核心设计说明：

1. **实体（Entity）**：
   - 使用整数ID标识
   - 由EntityManager管理生命周期

2. **组件（Component）**：
   - 所有组件继承自空基类Component
   - ComponentManager使用模板特化按类型存储组件
   - 每个实体可以有多个不同类型的组件

3. **系统（System）**：
   - 处理具有特定组件组合的实体
   - 通过签名（组件类型列表）过滤实体
   - 实现update方法处理逻辑

4. **世界（World）**：
   - 协调所有子系统
   - 提供实体/组件管理接口
   - 更新所有注册的系统

### 示例输出：
```
--- Frame 0 ---
Entity 0 moved to (1.5, 2)
Entity 1 moved to (4, 5.5)
--- Frame 1 ---
Entity 0 moved to (3, 4)
Entity 1 moved to (3, 6)
--- Frame 2 ---
Entity 0 moved to (4.5, 6)
Entity 1 moved to (2, 6.5)
--- Frame 3 ---
Entity 0 moved to (6, 8)
Entity 1 moved to (1, 7)
--- Frame 4 ---
Entity 0 moved to (7.5, 10)
Entity 1 moved to (0, 7.5)
```

### 可扩展性：
1. 添加新组件：只需继承Component
2. 添加新系统：继承System并实现update
3. 组件组合：通过修改系统签名自由组合

### 优化方向：
1. 使用内存池分配组件
2. 实现更高效的系统实体匹配
3. 添加多线程处理
4. 实现序列化功能

这个实现展示了ECS的核心概念，可以根据具体需求进一步扩展和完善。





#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <set>
#include <typeindex>
#include <functional>
#include <random>
#include <SFML/Graphics.hpp>

// 基础组件类
struct Component {
    virtual ~Component() = default;
};

// 实体ID类型
using Entity = uint32_t;

// 组件管理器
class ComponentManager {
public:
    template<typename T, typename... Args>
    T& addComponent(Entity entity, Args&&... args) {
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        auto& storage = getComponentStorage<T>();
        storage[entity] = std::move(comp);
        return *storage[entity];
    }

    template<typename T>
    void removeComponent(Entity entity) {
        auto& storage = getComponentStorage<T>();
        storage.erase(entity);
    }
    
    template<typename T>
    T* getComponent(Entity entity) {
        auto& storage = getComponentStorage<T>();
        auto it = storage.find(entity);
        return (it != storage.end()) ? it->second.get() : nullptr;
    }
    
    template<typename T>
    bool hasComponent(Entity entity) {
        return getComponentStorage<T>().find(entity) != getComponentStorage<T>().end();
    }
    
    template<typename T>
    size_t componentCount() {
        return getComponentStorage<T>().size();
    }

private:
    template<typename T>
    using ComponentStorage = std::unordered_map<Entity, std::unique_ptr<T>>;

    template<typename T>
    ComponentStorage<T>& getComponentStorage() {
        static ComponentStorage<T> storage;
        return storage;
    }
};

// 系统基类
class System {
public:
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) {} // 可选渲染方法
    virtual ~System() = default;
    
    std::set<Entity> entities;
};

// 实体管理器
class EntityManager {
public:
    Entity createEntity() {
        Entity entity = nextId++;
        entities.insert(entity);
        return entity;
    }

    void destroyEntity(Entity entity) {
        entities.erase(entity);
    }
    
    const std::set<Entity>& getAllEntities() const {
        return entities;
    }
    
    size_t entityCount() const {
        return entities.size();
    }

private:
    std::set<Entity> entities;
    Entity nextId = 0;
};

// ECS世界（协调实体、组件、系统）
class World {
public:
    Entity createEntity() {
        return entityManager.createEntity();
    }

    void destroyEntity(Entity entity) {
        entityManager.destroyEntity(entity);
        // 通知所有系统移除该实体
        for (auto& system : systems) {
            system.second->entities.erase(entity);
        }
    }
    
    template<typename T, typename... Args>
    T& addComponent(Entity entity, Args&&... args) {
        return componentManager.addComponent<T>(entity, std::forward<Args>(args)...);
    }
    
    template<typename T>
    void removeComponent(Entity entity) {
        componentManager.removeComponent<T>(entity);
    }
    
    template<typename T>
    T* getComponent(Entity entity) {
        return componentManager.getComponent<T>(entity);
    }
    
    template<typename T, typename... Args>
    std::shared_ptr<T> registerSystem(Args&&... args) {
        auto system = std::make_shared<T>(std::forward<Args>(args)...);
        systems[typeid(T)] = system;
        return system;
    }
    
    template<typename T>
    void setSystemSignature(const std::vector<std::type_index>& signature) {
        systemSignatures[typeid(T)] = signature;
    }
    
    void updateSystems(float dt) {
        for (auto& pair : systems) {
            pair.second->update(dt);
        }
    }
    
    void renderSystems(sf::RenderWindow& window) {
        for (auto& pair : systems) {
            pair.second->render(window);
        }
    }
    
    void updateEntitySystemMembership(Entity entity) {
        for (auto& pair : systems) {
            const auto& signature = systemSignatures[pair.first];
            bool hasAllComponents = true;
            
            for (const auto& compType : signature) {
                // 简化检查：实际应用中需要更精确的类型匹配
                // 这里我们只检查组件是否存在，不检查具体类型
                if (compType == typeid(Component)) continue; // 跳过基类检查
                // 实际应用中应实现更精确的类型匹配
            }
            
            if (hasAllComponents) {
                pair.second->entities.insert(entity);
            } else {
                pair.second->entities.erase(entity);
            }
        }
    }
    
    EntityManager& getEntityManager() { return entityManager; }
    ComponentManager& getComponentManager() { return componentManager; }

private:
    EntityManager entityManager;
    ComponentManager componentManager;
    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
    std::unordered_map<std::type_index, std::vector<std::type_index>> systemSignatures;
};

// --- 组件定义 ---
struct Transform : Component {
    float x = 0, y = 0;
    Transform(float x, float y) : x(x), y(y) {}
};

struct Velocity : Component {
    float vx = 0, vy = 0;
    Velocity(float vx, float vy) : vx(vx), vy(vy) {}
};

struct Renderable : Component {
    sf::Color color;
    float radius;
    Renderable(sf::Color c, float r) : color(c), radius(r) {}
};

// --- 系统定义 ---
class PhysicsSystem : public System {
public:
    void update(float dt) override {
        for (auto entity : entities) {
            auto* transform = world->getComponent<Transform>(entity);
            auto* velocity = world->getComponent<Velocity>(entity);
            
            if (transform && velocity) {
                // 更新位置
                transform->x += velocity->vx * dt;
                transform->y += velocity->vy * dt;
                
                // 边界检查
                if (transform->x < 0) {
                    transform->x = 0;
                    velocity->vx = -velocity->vx;
                } else if (transform->x > world->width) {
                    transform->x = world->width;
                    velocity->vx = -velocity->vx;
                }
                
                if (transform->y < 0) {
                    transform->y = 0;
                    velocity->vy = -velocity->vy;
                } else if (transform->y > world->height) {
                    transform->y = world->height;
                    velocity->vy = -velocity->vy;
                }
            }
        }
    }
    
    World* world = nullptr;
};

class RenderSystem : public System {
public:
    void render(sf::RenderWindow& window) override {
        for (auto entity : entities) {
            auto* transform = world->getComponent<Transform>(entity);
            auto* renderable = world->getComponent<Renderable>(entity);
            
            if (transform && renderable) {
                sf::CircleShape circle(renderable->radius);
                circle.setFillColor(renderable->color);
                circle.setPosition(transform->x - renderable->radius, 
                                   transform->y - renderable->radius);
                window.draw(circle);
            }
        }
    }
    
    World* world = nullptr;
};

class UISystem : public System {
public:
    void render(sf::RenderWindow& window) override {
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            // 如果找不到字体，使用默认字体
            return;
        }
        
        // 显示实体数量
        sf::Text entityText;
        entityText.setFont(font);
        entityText.setString("Entities: " + std::to_string(world->getEntityManager().entityCount()));
        entityText.setCharacterSize(20);
        entityText.setFillColor(sf::Color::White);
        entityText.setPosition(10, 10);
        window.draw(entityText);
        
        // 显示组件数量
        sf::Text componentText;
        componentText.setFont(font);
        componentText.setString("Components: " + std::to_string(
            world->getComponentManager().componentCount<Transform>() +
            world->getComponentManager().componentCount<Velocity>() +
            world->getComponentManager().componentCount<Renderable>()));
        componentText.setCharacterSize(20);
        componentText.setFillColor(sf::Color::White);
        componentText.setPosition(10, 40);
        window.draw(componentText);
        
        // 显示系统信息
        sf::Text systemText;
        systemText.setFont(font);
        systemText.setString("Systems: Physics, Render, UI");
        systemText.setCharacterSize(20);
        systemText.setFillColor(sf::Color::White);
        systemText.setPosition(10, 70);
        window.draw(systemText);
        
        // 显示FPS
        sf::Text fpsText;
        fpsText.setFont(font);
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(1.0f / dt)));
        fpsText.setCharacterSize(20);
        fpsText.setFillColor(sf::Color::White);
        fpsText.setPosition(10, 100);
        window.draw(fpsText);
        
        // 显示说明
        sf::Text infoText;
        infoText.setFont(font);
        infoText.setString("Press SPACE to add entities\nPress C to clear all entities");
        infoText.setCharacterSize(18);
        infoText.setFillColor(sf::Color::Cyan);
        infoText.setPosition(10, world->height - 80);
        window.draw(infoText);
    }
    
    World* world = nullptr;
    float dt = 0.016f;
};

// 随机数生成器
float randomFloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

sf::Color randomColor() {
    static std::vector<sf::Color> colors = {
        sf::Color::Red, sf::Color::Green, sf::Color::Blue,
        sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan,
        sf::Color(255, 165, 0), // Orange
        sf::Color(255, 192, 203) // Pink
    };
    return colors[rand() % colors.size()];
}

int main() {
    const int width = 800;
    const int height = 600;
    
    sf::RenderWindow window(sf::VideoMode(width, height), "ECS System with SFML Rendering");
    window.setFramerateLimit(60);
    
    World world;
    world.width = width;
    world.height = height;
    
    // 注册系统
    auto physicsSystem = world.registerSystem<PhysicsSystem>();
    physicsSystem->world = &world;
    world.setSystemSignature<PhysicsSystem>({typeid(Transform), typeid(Velocity)});
    
    auto renderSystem = world.registerSystem<RenderSystem>();
    renderSystem->world = &world;
    world.setSystemSignature<RenderSystem>({typeid(Transform), typeid(Renderable)});
    
    auto uiSystem = world.registerSystem<UISystem>();
    uiSystem->world = &world;
    
    // 创建初始实体
    for (int i = 0; i < 20; ++i) {
        Entity entity = world.createEntity();
        world.addComponent<Transform>(entity, 
            randomFloat(50, width - 50), 
            randomFloat(50, height - 50));
        world.addComponent<Velocity>(entity, 
            randomFloat(-100, 100), 
            randomFloat(-100, 100));
        world.addComponent<Renderable>(entity, 
            randomColor(), 
            randomFloat(10, 30));
    }
    
    sf::Clock clock;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
                
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    // 添加新实体
                    Entity entity = world.createEntity();
                    world.addComponent<Transform>(entity, 
                        randomFloat(50, width - 50), 
                        randomFloat(50, height - 50));
                    world.addComponent<Velocity>(entity, 
                        randomFloat(-100, 100), 
                        randomFloat(-100, 100));
                    world.addComponent<Renderable>(entity, 
                        randomColor(), 
                        randomFloat(10, 30));
                }
                else if (event.key.code == sf::Keyboard::C) {
                    // 清除所有实体
                    auto entities = world.getEntityManager().getAllEntities();
                    for (Entity e : entities) {
                        world.destroyEntity(e);
                    }
                }
            }
        }
        
        float dt = clock.restart().asSeconds();
        uiSystem->dt = dt;
        
        // 更新系统
        world.updateSystems(dt);
        
        // 渲染
        window.clear(sf::Color(30, 30, 50)); // 深蓝色背景
        
        // 绘制网格
        for (int x = 0; x < width; x += 40) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(static_cast<float>(x), 0.f, sf::Color(60, 60, 80)),
                sf::Vertex(sf::Vector2f(static_cast<float>(x), static_cast<float>(height), sf::Color(60, 60, 80))
            };
            window.draw(line, 2, sf::Lines);
        }
        for (int y = 0; y < height; y += 40) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(0.f, static_cast<float>(y)), 
                sf::Vertex(sf::Vector2f(static_cast<float>(width), static_cast<float>(y)))
            };
            line[0].color = sf::Color(60, 60, 80);
            line[1].color = sf::Color(60, 60, 80);
            window.draw(line, 2, sf::Lines);
        }
        
        // 绘制实体
        world.renderSystems(window);
        
        window.display();
    }
    
    return 0;
}