import pygame
import pygame.font
import os

white = (255, 255, 255)
red = (255, 50, 50)
green = (100, 255, 100)

path = os.path.dirname(os.path.abspath(__file__))
ifont = os.path.join(path, 'fonts', 'Nugo.ttf')

class Ants:
	"""Class to draw ants"""
	def __init__(self, lv):
		"""init ants"""

		self.screen = lv.screen
		self.screen_rect = self.screen.get_rect()
		self.settings = lv.settings
		self.line = self.settings.line
		self.grid = lv.grid
		self.rect = self.grid.rect
		self.rooms = self.settings.rooms
		self.ants = []

	def choose_colour(self, x_co, y_co, colour):
		"function that chooses which colour to print ant in"
		self.r = 255
		self.g = 100
		self.b = 0
		if colour == 1:
			self.g = 100
			self.b = 0
		elif colour == 2:
			self.g = 160
			self.b = 60
		elif colour == 3:
			self.g = 250
			self.b = 150
		orange = (self.r, self.g, self.b)
		occupied = pygame.Surface((self.settings.grid_side, self.settings.grid_side))
		occupied.fill(orange)

		self.screen.blit(occupied, (x_co, y_co))


	def draw_ants(self, line_s):
		"""functions for drawing the ants"""
		self.count_ants()
		i = 0
		if line_s == 'L-BREAK':
			self.settings.source_count = self.settings.ants
			self.settings.sink_count = 0
			self.count_ants()
			return
		line = line_s.split(' ')
		self.settings.ant_col += 1
		if self.settings.sink_count == self.settings.ants:
			self.settings.sink_count = 0
			self.settings.source_count = self.settings.ants
		while i < len(line):
			y_grid = self.rect.y
			x_grid = self.rect.x
			line_l = line[i].split('-')
			r_name = str(line_l[-1])
			a_num = int(line_l[0].strip('L'))
			add_ant = 1
			for ants in self.ants:
				if a_num == ants['ant_num']:
					add_ant = 0
					colour_num = ants['ant_col']
					if ants['first_move'] == r_name:
						self.settings.source_count -= 1
			if add_ant == 1:
				new_ant = {
					'ant_num': int(a_num),
					'ant_col': self.settings.ant_col,
					'first_move': r_name
				}
				self.ants.append(new_ant)
				colour_num = self.settings.ant_col
				self.settings.source_count -= 1
			for room in self.rooms:
				if room['name'] == r_name:
					room['used'] = 1
					x_grid += ((room['x'] - self.settings.smallestx) * (self.settings.scale_x))
					y_grid += ((room['y'] - self.settings.smallesty) * (self.settings.scale_y))
					if room['source'] == 1:
						self.screen.blit(self.settings.source_img, (x_grid, y_grid))
					elif room['sink'] == 1:
						self.settings.sink_count += 1
						self.screen.blit(self.settings.sink_img, (x_grid, y_grid))
					else:
						self.choose_colour(x_grid, y_grid, colour_num)
				elif room['used'] == 0:
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
			i += 1
		for room in self.rooms:
			room['used'] = 0
		if self.settings.ant_col == 3:
				self.settings.ant_col = 0
		self.count_ants()

	def	count_ants(self):
		"""This function will print the amount of ants
			in the source and sink
		"""
		count_font = pygame.font.Font(ifont, 30)

		src_count = str(self.settings.source_count)
		src_str = "{:}".format(src_count)
		src_print = count_font.render(src_str, True,
						green, self.settings.bg_colour)
		self.sink_count = str(self.settings.sink_count)
		self.sink_str = "{:}".format(self.sink_count)
		self.sink_print = count_font.render(self.sink_str, True,
						red, self.settings.bg_colour)

		self.source_clear = pygame.Rect(695, 90, 80, 50)
		self.screen.fill(self.settings.bg_colour, self.source_clear)
		self.sink_clear = pygame.Rect(695, 165, 80, 50)
		self.screen.fill(self.settings.bg_colour, self.sink_clear)
		self.screen.blit(src_print, (700, 95))
		self.screen.blit(self.sink_print, (700, 170))
