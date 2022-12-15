import pygame
import sys
from title import Title
from time import sleep
from settings import Settings
from grid import Grid
from ants import Ants

class Lem_in:
	"""Class for lem_in visualizer"""

	def __init__(self):
		"""Initialize the visualizer"""
		pygame.init()
		self.settings = Settings()
		self.screen = pygame.display.set_mode((
			self.settings.screen_width, self.settings.screen_height))
		pygame.display.set_caption("Lem_in Visualizer")

		self.settings.read_ants()
		self.settings.read_rooms()
		self.title = Title(self)
		self.grid = Grid(self)
		self.ants = Ants(self)

	def run_vis(self):
		"""Loops through program"""
		self.screen.fill(self.settings.bg_colour)
		self.title.draw_title_instructions()
		self.grid.draw_grid()
		i = 0
		while True:
			if i == self.settings.i:
				i = 0
			pygame.display.flip()
			self._check_events()
			if self.settings.split_line[i][:1] == 'L':
				self.ants.draw_ants(self.settings.split_line[i])
			
			pygame.time.delay(int(self.settings.delay))
			i += 1

	def pause_vis(self):
		"""Function that pauses the game"""
		paused = True
		while paused:
			for event in pygame.event.get():
				if event.type == pygame.KEYDOWN:
					if event.key == pygame.K_q:
						pygame.quit()
						exit()
					if event.key == pygame.K_SPACE:
						paused = False
						pygame.display.update()
				if event.type == pygame.QUIT:
					pygame.quit()
					exit()


	def _check_events(self):
		"""Function that check events in the program"""
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				sys.exit()
			elif event.type == pygame.KEYDOWN:
				if event.key == pygame.K_q:
					sys.exit()
				#check buttons or speed
				if event.key == pygame.K_DOWN:
					self.settings.delay *= 1.1
				if event.key == pygame.K_UP:
					self.settings.delay /= 1.1
				if event.key == pygame.K_SPACE:
					self.pause_vis()

if __name__ == '__main__':
	lv = Lem_in()
	lv.run_vis()