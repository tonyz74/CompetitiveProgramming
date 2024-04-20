#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;
using i64 = long long;

int main(void) {
    i64 N, K; cin >> N >> K;
    i64 node_cnt = K;

    i64 time = 0;

    // groups with at least 1 free
    set<i64> free_groups;
    map<i64, i64> succ;
    map<i64, i64> capacity;

    i64 bessie_group = -1;

    vector<vector<i64> > graph(node_cnt + 1, vector<i64>());

    vector<i64> duration(N + 1);
    for (i64 i = 1; i <= N; i++) {
        cin >> duration[i];
    }

    // the groups whose interviews ended at a particular time
    map<i64, vector<i64> > interview_ends;

    for (i64 i = 1; i <= K; i++) {
        // farmer i's interview will end at duration[i] + time
        interview_ends[duration[i] + time].push_back(i);
        succ[i] = i;
        capacity[i] = 0;
    }

    i64 curr_cow = K + 1;

    function<i64(i64, i64)> descend = [&] (i64 now, i64 add) {
        if (succ[now] == now) {
            capacity[now] += add;
            return succ[now];
        }

        capacity[now] += add;
        succ[now] = descend(succ[now], add);
        return succ[now];
    };

    while (!interview_ends.empty()) {
        // printf("\n\n");
        time = interview_ends.begin()->first;

        // printf("time is %lld\n", time);

        // happens at the same time
        vector<i64>& earliest = interview_ends.begin()->second;

        i64 new_group = ++node_cnt;
        graph.push_back(vector<i64>());

        i64 has = 0;
        for (i64 end: earliest) {
            // printf("freed %lld ", end);
            free_groups.insert(descend(end, 1));
            // printf("which became %lld\n", now);
        }

        for (i64 x: free_groups) {
            x = descend(x, 0);
            has += capacity[x];
            graph[new_group].push_back(x);
            succ[x] = new_group;
            // printf("connected %lld to %lld\n", x, new_group);
        }

        free_groups.clear();
        succ[new_group] = new_group;

        while (has > 0) {
            // is bessie
            if (curr_cow == N + 1) {
                bessie_group = new_group;
                goto done;
            }

            interview_ends[time + duration[curr_cow]].push_back(new_group);

            has--;
            curr_cow++;
        }

        capacity[new_group] = has;
        if (has > 0) {
            free_groups.insert(new_group);
        }

        interview_ends.erase(interview_ends.begin());
    }

    // printf("\n\n");

    done: (void) 0;
    printf("%lld\n", time);

    set<i64> seen_all;
    vector<bool> seen_farmers(K + 1);

    function<void(i64)> dfs = [&] (i64 now) {

        if (now <= K) seen_farmers[now] = true;
        seen_all.insert(now);

        for (i64 x: graph[now]) {
            // printf("conn: %lld\n", x);
            if (!seen_all.count(x)) {
                dfs(x);
            }
        }
    };

    dfs(bessie_group);

    for (i64 f = 1; f <= K; f++) {
        if (seen_farmers[f]) printf("1");
        else printf("0");
    }
    printf("\n");

}