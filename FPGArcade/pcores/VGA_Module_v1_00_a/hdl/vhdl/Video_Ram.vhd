----------------------------------------------------------------------------------
-- Company: Loras College
-- Engineer: Nick Burek
-- 
-- Create Date:    17:41:14 03/28/2011 
-- Design Name: 
-- Module Name:    Video_Ram - Behavioral 
-- Project Name: FPGArcade
-- Target Devices: Nexys2 Board
-- Tool versions: 
-- Description: Handles the storage of all the tile and block data for the
--				graphics. It evaluates the graphic instruction operations. It 
--				stores 64 tiles that each contain an 8x8 array of 8-bit colors as 
--				well as 4800 blocks for the background and 16 moveable blocks. 
--				For each block it stores 5 bits of data that specifies the address
--				of a tile in the tileSet. When you want to display that block it 
--				uses the tile address to reference which tile it should pull the
--				pixel data from. There are 4800 background blocks arranged in an
--				80x60 array and 16 moveable blocks that are stored after the 
--				background blocks. Moveable blocks can be placed at any position, 
--				whereas background blocks have a fixed position. 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity Video_Ram is
    Port ( 	clk50Mhz : in STD_LOGIC;
			instruction : in  STD_LOGIC_VECTOR(31 downto 0);
			instructionClk : in STD_LOGIC;
			positionX : in  STD_LOGIC_VECTOR(9 downto 0);
			positionY : in  STD_LOGIC_VECTOR(8 downto 0);
			currentPixel : out  STD_LOGIC_VECTOR(7 downto 0));
end Video_Ram;

architecture Behavioral of Video_Ram is

-- declare the BRAM controller for the tile data
component tile_graphics_bram
	port (
	clka: in std_logic;
	wea: in std_logic_vector(0 downto 0);
	addra: in std_logic_vector(11 downto 0);
	dina: in std_logic_vector(7 downto 0);
	clkb: in std_logic;
	addrb: in std_logic_vector(11 downto 0);
	doutb: out std_logic_vector(7 downto 0));
end component;

-- Synplicity black box declaration
attribute syn_black_box : boolean;
attribute syn_black_box of tile_graphics_bram: component is true;

-- declare the BRAM controller for the blcok data
component block_graphics_bram
	port (
	clka: in std_logic;
	wea: in std_logic_vector(0 downto 0);
	addra: in std_logic_vector(12 downto 0);
	dina: in std_logic_vector(5 downto 0);
	clkb: in std_logic;
	addrb: in std_logic_vector(12 downto 0);
	doutb: out std_logic_vector(5 downto 0));
end component;

-- Synplicity black box declaration
attribute syn_black_box of block_graphics_bram: component is true;

-- define the signals needed for the tileSet data BRAM
signal tileSetWrAddr : std_logic_vector(11 downto 0);
signal tileSetReAddr : std_logic_vector(11 downto 0);
signal tileSetOutputData : std_logic_vector(7 downto 0);
signal tileSetInputData : std_logic_vector(7 downto 0);
signal WEA : std_logic_vector(0 downto 0) := "1";

-- define the signals needed for the block data BRAM
signal blockSetWrAddr : std_logic_vector(12 downto 0):= "0000000000000";
signal blockSetReAddr : std_logic_vector(12 downto 0):= "0000000000000";
signal blockSetOutputData : std_logic_vector(5 downto 0):= "000000";
signal blockSetInputData : std_logic_vector(5 downto 0):= "000000";

-- define the signals needed to store data for the moveable blocks 
-- These are not stored in BRAM because they need to be accessed instantly and randomly
type transparencySet is array(1023 downto 0) of STD_LOGIC; -- each moveable block has 64 bits that define which pixels in its 8x8 array are visible
signal movingBlocksTransparencyMap : transparencySet := (others => '0'); -- the transparency maps for the moveable blocks
type moving_blocks_x is array (15 downto 0) of STD_LOGIC_VECTOR(9 downto 0); -- the x coordinates of all the moving tile
type moving_blocks_y is array (15 downto 0) of STD_LOGIC_VECTOR(8 downto 0); -- the y coordinates of all the moving tile
signal movingBlocksX : moving_blocks_x := (others => "1010000000"); -- initialize them to all be offscreen at the start
signal movingBlocksY : moving_blocks_y := (others => "000000000");

-- used to remember which pixel you want from the tileSet
signal tileX : STD_LOGIC_VECTOR(2 downto 0);
signal tileY : STD_LOGIC_VECTOR(2 downto 0);

signal invClk50Mhz : STD_LOGIC; -- used for the tileSet BRAM so that it updates after the data is available on the dataOut signal of the block BRAM

begin
invClk50Mhz <= Not clk50Mhz; -- an inverted 50Mhz clock used to tell the tileSetBRAM when to update

-- Block RAM that holds the data for the tile set
tileSetBRAM : tile_graphics_bram
		port map (
			clka => clk50Mhz,
			wea => WEA,
			addra => tileSetWrAddr,
			dina => tileSetInputData,
			clkb => invClk50Mhz,
			addrb => tileSetReAddr,
			doutb => currentPixel);

-- Block RAM that holds the data saying which tiles the blocks are mapped to
blockSetBRAM : block_graphics_bram
		port map (
			clka => clk50Mhz,
			wea => WEA,
			addra => blockSetWrAddr,
			dina => blockSetInputData,
			clkb => clk50Mhz,
			addrb => blockSetReAddr,
			doutb => blockSetOutputData);
			
-- process that starts fetching the pixel data to be outputted
-- it checks which block the position is currently in and starts
-- looking up the address for the tile it is set to
process (positionX, positionY)
	variable tempX : integer;
	variable tempY : integer;
begin
	-- figure out which background block it is in and set the read data to that information
	blockSetReAddr <= conv_std_logic_vector(conv_integer(positionY(8 downto 3))*80 + conv_integer(positionX(9 downto 3)),13);
	tileX <= positionX(2 downto 0);
	tileY <= positionY(2 downto 0);
	
	-- start testing the moving blocks
	for i in 15 downto 0 loop
	
		-- get the X and Y positions of the moveable block
		tempX := conv_integer(movingBlocksX(i)(9 downto 0));
		tempY := conv_integer(movingBlocksY(i)(8 downto 0));
		
		-- check if it's inside this moving block
		if (positionX>=tempX and positionX<=(tempX+7) and
				positionY>=tempY and positionY<=(tempY+7)) then
			
			-- check if the bit is on is transparent or not, if not change the read data
			if (movingBlocksTransparencyMap(conv_integer(conv_std_logic_vector(i,6) & conv_std_logic_vector(conv_integer(positionY-tempY),3) & conv_std_logic_vector(conv_integer(positionX-tempX),3))) = '0') then
				blockSetReAddr <= conv_std_logic_vector(4800 + i,13);
				tileX <= conv_std_logic_vector(conv_integer(positionX-tempX),3);
				tileY <= conv_std_logic_vector(conv_integer(positionY-tempY),3);
			end if; 
		end if; 
	end loop;
		
end process;

-- Process that finishes fetching the pixel data. It executes
-- when the block data BRAM outputs the address it needs to read
-- from. All it does is set the read address of the tileSet BRAM
-- so that it will output the pixel data you need from the proper
-- tile. 
process (blockSetOutputData)
begin
	tileSetReAddr <= blockSetOutputData & tileX(2 downto 0) & tileY(2 downto 0);
end process;

-- Process that handles the graphics instruction operations. 
-- Instructions are executed when the instruction clock goes
-- from low to high. See the documentation for information
-- about the OP codes.
process (instructionClk)
begin
		if (instructionClk'EVENT AND instructionClk = '1') then -- ready clock acts kind of like a ready bit to tell when the instruction is ready
			if instruction(31 downto 29) = "000" then -- set pixel in tile
				tileSetWrAddr <= instruction(19 downto 8);
				tileSetInputData <= instruction(7 downto 0);
			elsif instruction(31 downto 29) = "001" then -- set row transparency on moveable block
				movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "111")) <= instruction(7);
				movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "110")) <= instruction(8);
				movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "101")) <= instruction(9);
				movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "100")) <= instruction(10);
				movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "011")) <= instruction(11);
				movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "010")) <= instruction(12);
				movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "001")) <= instruction(13);
				movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "000")) <= instruction(14);
			elsif instruction(31 downto 29) = "010" then -- change location of moveable block
				movingBlocksX(conv_integer(instruction(22 downto 19))) <= instruction(9 downto 0);
				movingBlocksY(conv_integer(instruction(22 downto 19))) <= instruction(18 downto 10);
			elsif instruction(31 downto 29) = "011" then -- set moveable block's tile reference
				blockSetWrAddr <= conv_std_logic_vector(4800 + conv_integer(instruction(3 downto 0)),13);
				blockSetInputData <= instruction(9 downto 4);
			elsif instruction(31 downto 29) = "100" then -- set background block
				blockSetWrAddr <= conv_std_logic_vector(conv_integer(instruction(12 downto 7))*80 + conv_integer(instruction(6 downto 0)),13);
				blockSetInputData <= instruction(18 downto 13);
			end if;
		end if;

end process;
			
end Behavioral;

