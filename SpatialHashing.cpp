#include <unordered_map>
#include <vector>
#include <cmath>

struct Vec3 {
    float x, y, z;
};

struct Entity {
    int id;
    Vec3 position;
};

class SpatialHash {
public:
    SpatialHash(float cell_size) : cell_size_(cell_size) {}

    void clear() {
        grid_.clear();
    }

    void insert(const Entity& entity) {
        auto key = hash_position(entity.position);
        grid_[key].push_back(&entity);
    }

    std::vector<const Entity*> query_neighbors(const Vec3& position) {
        std::vector<const Entity*> result;

        auto [cx, cy, cz] = cell_coords(position);

        // Check neighboring cells (important!)
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dz = -1; dz <= 1; ++dz) {
                    auto key = hash_coords(cx + dx, cy + dy, cz + dz);

                    if (grid_.count(key)) {
                        const auto& bucket = grid_[key];
                        result.insert(result.end(), bucket.begin(), bucket.end());
                    }
                }
            }
        }

        return result;
    }

private:
    float cell_size_;

    std::unordered_map<size_t, std::vector<const Entity*>> grid_;

    // Convert position → integer cell
    std::tuple<int, int, int> cell_coords(const Vec3& pos) const {
        return {
            static_cast<int>(std::floor(pos.x / cell_size_)),
            static_cast<int>(std::floor(pos.y / cell_size_)),
            static_cast<int>(std::floor(pos.z / cell_size_))
        };
    }

    // Hash 3D coordinates into a single key
    size_t hash_coords(int x, int y, int z) const {
        const size_t p1 = 73856093;
        const size_t p2 = 19349663;
        const size_t p3 = 83492791;

        return (x * p1) ^ (y * p2) ^ (z * p3);
    }

    size_t hash_position(const Vec3& pos) const {
        auto [x, y, z] = cell_coords(pos);
        return hash_coords(x, y, z);
    }
};