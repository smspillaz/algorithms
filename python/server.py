class ServerTime:
    def __init__(self):
        self.jobs = []
        self.used = 0


def serverFarm(jobs, servers):
    serverArray = [ServerTime() for i in range(0, servers)]
    
    # Greedy approach - re-arrange jobs into
    # a list of index/tuple and then sort by
    # the time taken for each job, then assign
    # to each server the next time it will be
    # available
    jobsArray = reversed(sorted([(i, j) for i, j in enumerate(jobs)],
                       key=j))
    
    for job_index, job_time in jobsArray:
        # Find the server with the shortest time
        best_time = 100 * 1000
        serverToUse = None
        for server in serverArray:
            if server.used < best_time:
                serverToUse = server
        
        # Allocate the job to that server
        serverToUse.jobs.append(job_index)
        serverToUse.used += job_time
    
    return [s.jobs for s in serverArray]
