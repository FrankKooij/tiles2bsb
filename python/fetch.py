import sys, os, urllib2, math
from Queue import Queue
from threading import Thread

def deg2num(lat_deg, lon_deg, zoom):
	lat_rad = math.radians(lat_deg)
	n = 2.0 ** zoom
	xtile = int((lon_deg + 180.0) / 360.0 * n)
	ytile = int((1.0 - math.log(math.tan(lat_rad) + (1 / math.cos(lat_rad))) / math.pi) / 2.0 * n)
	return (xtile, ytile)

north = [55.528631,3.468246]
south = [47.174778,15.772934]

def download(k):
	z = k[0]
	x = k[1]
	y = k[2]
	d = "images/" + str(z) + "/" + str(x) + "/"
	try:
		os.makedirs(d)
	except:
		pass

	try:

		n = d + str(y) + ".png"
		
		if os.path.isfile(n):
			return True

		f = open(n, "wb")
		u = urllib2.urlopen("http://a.tile.osm.org/" + str(z) + "/" + str(x) + "/" + str(y) + ".png")
		if u.getcode() == 200:
			f.write(u.read())
			f.close()
			return True
		else:
			return False

	except urllib2.HTTPError as e:

		# we have a 404
		os.remove(n)
		return False

# Thread executing tasks from a given tasks queue
class Worker(Thread):
    def __init__(self, tasks):
        Thread.__init__(self)
        self.tasks = tasks
        self.daemon = True
        self.start()
    
    def run(self):
        while True:
            func, args, kargs = self.tasks.get()
            try: func(*args, **kargs)
            except Exception, e: print e
            self.tasks.task_done()

# Pool of threads consuming tasks from a queue
class ThreadPool:
    def __init__(self, num_threads):
        self.tasks = Queue(num_threads)
        for _ in range(num_threads): Worker(self.tasks)

    def add_task(self, func, *args, **kargs):
        self.tasks.put((func, args, kargs))

    def wait_completion(self):
        self.tasks.join()

pool = ThreadPool(200)

for z in range(0, 17):

	print "zoomlevel", z

	# geofencing
	tile_north = deg2num(north[0], north[1], z)
	tile_south = deg2num(south[0], south[1], z)
	print "tile_north", tile_north
	print "tile_south", tile_south

	for xx in range(tile_north[0], tile_south[0]+1):
		for yy in range(tile_north[1], tile_south[1]+1):
			pool.add_task(download, [z, xx, yy])

	pool.wait_completion()