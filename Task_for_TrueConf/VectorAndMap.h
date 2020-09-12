#pragma once
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>


namespace VectorAndMap
{
    static const size_t scs_min_lim = 1;
    static const size_t scs_max_lim = 9;

    static const size_t scs_min_lim_delete = 1;
    static const size_t scs_max_lim_delete = 15;

    template<typename T>
    void GenerateConteinerElements(T& conteiner, size_t conteiner_size)
    {
        for (size_t i = 0; i < conteiner_size; ++i)
        {
            conteiner[i] = rand() % scs_max_lim + scs_min_lim;
        }
    }

    template<typename Map, typename Vector>
    void DeleteConteinerElements(Map& map_for_delete, Vector& vector_for_delete)
    {
        const size_t count_to_delete = rand() % scs_max_lim_delete + scs_min_lim_delete;

        if (count_to_delete >= vector_for_delete.size())
        {
            vector_for_delete.clear();
            map_for_delete.clear();

            return;
        }

        auto iter = map_for_delete.begin();

        for (size_t i = 0; i < count_to_delete; ++i)
        {
            size_t index = rand() % (vector_for_delete.size() - 1);
            std::advance(iter, index);

            map_for_delete.erase(iter);
            vector_for_delete.erase(vector_for_delete.begin() + index);

            iter = map_for_delete.begin();
        }
    }


    template<typename Map, typename Vec>
    Vec GetIntersection(Map& map_for_sync, Vec vector_for_sync_copy)
    {
        Vec map_transform_to_vector(map_for_sync.size());
        Vec intersection(vector_for_sync_copy.size());

        std::sort(vector_for_sync_copy.begin(), vector_for_sync_copy.end());

        auto iter = map_transform_to_vector.begin();
        for (const auto& [key, value] : map_for_sync)
        {
            *iter = value;
            ++iter;
        }

        std::sort(map_transform_to_vector.begin(), map_transform_to_vector.end());

        std::set_intersection(vector_for_sync_copy.begin(), vector_for_sync_copy.end(),
                              map_transform_to_vector.begin(), map_transform_to_vector.end(),
                              std::back_inserter(intersection));

        return intersection;
    }
    
    template<typename Vec>
    void EraseFromVector(Vec& vector_for_erase, Vec& intersection)
    {
        auto pred = [&intersection](int container_element)
                    {
                        for (auto& i : intersection) { if (container_element == i) { return false; } }
                        return true;
                    };

        vector_for_erase.erase(
            remove_if(vector_for_erase.begin(), vector_for_erase.end(), pred),
            vector_for_erase.end());
    }

    template<typename Map, typename Vec>
    void EraseFromMap(Map& map_for_erase, Vec& intersection)
    {
        auto pred = [&intersection](std::pair<const int, int>& container_element)
                    {
                        for (auto& i : intersection) { if (i == container_element.second) { return false; } }
                        return true;
                    };

        auto iter = map_for_erase.begin();
        while ((iter = find_if(iter, map_for_erase.end(), pred)) != map_for_erase.end()) {
            map_for_erase.erase(iter++);
        }
    }

    template<typename Map, typename Vec>
    void SynchronizeConteiners(Map& map_for_sync, Vec& vector_for_sync)
    {
        Vec intersection(GetIntersection(map_for_sync, vector_for_sync));

        EraseFromVector(vector_for_sync, intersection);

        EraseFromMap(map_for_sync, intersection);
    }
};

