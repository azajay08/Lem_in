import pygame
import pygame.font

white_blue = (170, 230, 255)

class Grid:
	"""Class for the grid(map)"""
	def __init__(self, lv):
		"""Init grid"""

		self.screen = lv.screen
		self.screen_rect = self.screen.get_rect()
		self.settings = lv.settings

		self.width, self.height = 800, 400

		self.rect = pygame.Rect(0, 0, self.width, self.height)
		self.rect.x = 200
		self.rect.y = 280

	def draw_grid(self):
		"""draws the rooms and links"""
		y_grid = self.rect.y
		x_grid = self.rect.x
		center_xy = self.settings.grid_side / 2
		# center_mid = (self.settings.grid_side / 3) / 2
		self.links = []
		for room in self.settings.rooms:
			x_grid += ((room['x'] - self.settings.smallestx) * (self.settings.scale_x))
			y_grid += ((room['y'] - self.settings.smallesty) * (self.settings.scale_y))
			new_link = {
				'name': room['name'],
				'x_c': float(x_grid + center_xy),
				'y_c': float(y_grid + center_xy),
			}
			self.links.append(new_link)
			y_grid = self.rect.y
			x_grid = self.rect.x
		for connections in self.settings.connect:
			for link in self.links:
				if connections['l_1'] == link['name']:
					link1 = int(link['x_c']), int(link['y_c'])
					# x1 = int(link['x_c'])
					# y1 = int(link['y_c'])
			for link in self.links:
				if connections['l_2'] == link['name']:
					link2 = int(link['x_c']), int(link['y_c'])
					# x2 = int(link['x_c'])
					# y2 = int(link['y_c'])
			# coord_x = (x1 + x2) / 2 - center_mid
			# coord_y = (y1 + y2) / 2 - center_mid
			pygame.draw.line(self.screen, white_blue, (link1), (link2))
			# self.screen.blit(self.settings.midway, (coord_x, coord_y))
		for room in self.settings.rooms:
			x_grid += ((room['x'] - self.settings.smallestx) * (self.settings.scale_x))
			y_grid += ((room['y'] - self.settings.smallesty) * (self.settings.scale_y))
			if room['source'] == 1:
				self.screen.blit(self.settings.source_img, (x_grid, y_grid))
			elif room['sink'] == 1:
				self.screen.blit(self.settings.sink_img, (x_grid, y_grid))
			else:
				self.screen.blit(self.settings.room_img, (x_grid, y_grid))
			y_grid = self.rect.y
			x_grid = self.rect.x
