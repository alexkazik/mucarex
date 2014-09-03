--
-- Copyright (c) 2014 ALeX Kazik
-- All rights reserved.
--
-- Redistribution and use in source and binary forms, with or without
-- modification, are permitted provided that the following conditions are met:
--
-- * Redistributions of source code must retain the above copyright notice, this
--   list of conditions and the following disclaimer.
--
-- * Redistributions in binary form must reproduce the above copyright notice,
--   this list of conditions and the following disclaimer in the documentation
--   and/or other materials provided with the distribution.
--
-- * Neither the names MuCaREX, p1x3l.net nor the names of its
--   contributors may be used to endorse or promote products derived from
--   this software without specific prior written permission.
--
-- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
-- AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
-- IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
-- DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
-- FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
-- DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
-- SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
-- CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
-- OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
-- OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
--

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity MuCaREX is
	Generic (
		c_mode_bootup : STD_LOGIC_VECTOR(1 downto 0) := "00";
		c_mode_ram : STD_LOGIC_VECTOR(1 downto 0) := "01";
		c_mode_32k : STD_LOGIC_VECTOR(1 downto 0) := "10";
		c_mode_64k : STD_LOGIC_VECTOR(1 downto 0) := "11";
		c_use_simple_reset_detection : BOOLEAN := false
	);
	Port (
		i_vec_addr : in STD_LOGIC_VECTOR (15 downto 0);
		io_vec_data : inout STD_LOGIC_VECTOR (7 downto 7) := "Z";
		i_vec_rw : in STD_LOGIC;
		i_n_vec_e : in STD_LOGIC;
		i_vec_pb6 : in STD_LOGIC;
		o_n_led : out STD_LOGIC;
		o_rom_addr : out STD_LOGIC_VECTOR (18 downto 12);
		o_n_rom_cs1 : out STD_LOGIC := '1';
		o_n_rom_cs2 : out STD_LOGIC := '1';
		o_n_rom_oe : out STD_LOGIC := '1';
		o_ram_addr : out STD_LOGIC_VECTOR (14 downto 14);
		o_n_ram_cs : out STD_LOGIC := '1'
	);
end MuCaREX;

architecture Behavioral of MuCaREX is

	signal sig_mode : STD_LOGIC_VECTOR(1 downto 0) := c_mode_bootup;
	signal sig_master : STD_LOGIC := '1';

	signal sig_bank : STD_LOGIC_VECTOR (19 downto 12) := "00000000";
	signal sig_page : STD_LOGIC_VECTOR (19 downto 15);
	
	signal sig_ram_bank : STD_LOGIC ;
	signal sig_do_page : STD_LOGIC ;
	
	signal sig_reset_detect : STD_LOGIC_VECTOR (4 downto 0) := "00000";
	
	signal sig_temp_bank : STD_LOGIC_VECTOR (19 downto 12);
	
	signal sig_data_valid : STD_LOGIC := '0';
	signal sig_data_output : STD_LOGIC;
	
	signal sig_led : STD_LOGIC := '1';

	signal sig_ram_mode : boolean;
	signal sig_vpage : STD_LOGIC_VECTOR (19 downto 15);

begin

	sig_ram_mode <= sig_mode = c_mode_ram;

	o_n_ram_cs <= i_n_vec_e when
		(i_vec_addr(15)='0' and sig_ram_mode) or
		(i_vec_addr(15 downto 14)="10" and (not sig_ram_mode))
		else '1';
	
	o_ram_addr(14) <= i_vec_addr(14) when i_vec_addr(15)='0' else sig_ram_bank;
	
	sig_vpage <= "0000" & i_vec_pb6 when sig_mode(0)='1' else sig_page;
	
	sig_temp_bank(19 downto 12) <= STD_LOGIC_VECTOR( unsigned(sig_bank) + unsigned(sig_vpage(19 downto 15) & i_vec_addr(14 downto 12)) ) when
		sig_mode(1)='1'
		else "00000" & i_vec_addr(14 downto 12);
	
	o_n_rom_cs1 <= i_n_vec_e when
		sig_temp_bank(19)='0' and i_vec_addr(15)='0' and (i_vec_rw='1' or sig_master='1') and (not sig_ram_mode)
		else '1';
	o_n_rom_cs2 <= i_n_vec_e when
		sig_temp_bank(19)='1' and i_vec_addr(15)='0' and (i_vec_rw='1' or sig_master='1') and (not sig_ram_mode)
		else '1';
	
	o_rom_addr(18 downto 12) <= sig_temp_bank(18 downto 12);

	io_vec_data(7) <= sig_data_output when sig_data_valid='1' and i_n_vec_e='0' else 'Z';

	o_n_led <= '0' when sig_led='1' else 'Z';

	o_n_rom_oe <= not i_vec_rw;

	change: process (i_n_vec_e)
	begin
		if falling_edge(i_n_vec_e) then

			--
			-- register access
			--
			
			sig_data_valid <= '0';

			case i_vec_addr(3 downto 0) is
			when x"0" => sig_data_output <= sig_mode(0);
			when x"1" => sig_data_output <= sig_mode(1);
			when x"2" => sig_data_output <= sig_ram_bank;
			when x"3" => sig_data_output <= sig_led;
			when x"4" => sig_data_output <= sig_do_page;
			when x"5" => sig_data_output <= '0';
			when x"6" => sig_data_output <= '0';
			when x"7" => sig_data_output <= sig_master;
			when x"8" => sig_data_output <= sig_bank(12);
			when x"9" => sig_data_output <= sig_bank(13);
			when x"a" => sig_data_output <= sig_bank(14);
			when x"b" => sig_data_output <= sig_bank(15);
			when x"c" => sig_data_output <= sig_bank(16);
			when x"d" => sig_data_output <= sig_bank(17);
			when x"e" => sig_data_output <= sig_bank(18);
			when x"f" => sig_data_output <= sig_bank(19);
			when others => null;
			end case;
			
			if i_vec_addr(15 downto 10) = "110000" then -- $C0..$C3
				if i_vec_addr(9 downto 5) = "00000" and sig_do_page='1' then
					-- $c000-$c01f, any access: set PAGE to addr & 0x001f
					-- only when allowed (register do_page)
					sig_page(19 downto 15) <= i_vec_addr(4 downto 0);
				end if;
				if i_vec_rw = '1' and i_vec_addr(9 downto 4) = "010000" then
					-- read register (on $c100-$c10f, d7)
					sig_data_valid <= '1';
				end if;
				if i_vec_addr(9 downto 8) = "10" and sig_master = '1' and i_vec_addr(6 downto 5) = "00" then
					-- $c200-$c2ff, any access: set registers (all at once)
					-- only in master mode!
					sig_mode(0) <= i_vec_addr(0);
					sig_mode(1) <= i_vec_addr(1);
					sig_ram_bank <= i_vec_addr(2);
					sig_led <= i_vec_addr(3);
					sig_do_page <= i_vec_addr(4);
					-- '0' - checked
					-- '0' - checked
					sig_master <= i_vec_addr(7);
				end if;
				if i_vec_addr(9 downto 8) = "11" and sig_master = '1' then
					-- $c300-$c3ff, any access: switch bank
					-- only in master mode!
					sig_bank <= i_vec_addr(7 downto 0);
				end if;
			end if;
			
			--
			-- detect reset
			--

			if c_use_simple_reset_detection then

				-- detect a reset by simply reading the reset vector
				-- note: this can by "emulated" by e.g. "ldd $fffe"
				
				if i_vec_rw = '1' and i_vec_addr(15 downto 1) = "111111111111111" then -- $fffe/$ffff (reset vector)
					if i_vec_addr(0) = '0' then
						-- reading $fffe: remeber it
						sig_reset_detect(0) <= '1';
					elsif sig_reset_detect(0) = '1' then
						-- reading $ffff after an $fffe read: reset
						sig_mode <= c_mode_bootup;
						sig_master <= '1';
						sig_led <= '1';
					end if;
				else
					-- not an read to the reset-vector: forget if we remembered
					sig_reset_detect(0) <= '0';
				end if;

			else

				-- cycle accurate timing of reset
				--     do a reset OR jmp [fffe] -> read reset vector
				--   fffe (read hi "$f0__")
				--   ffff (read lo "$__00")
				--     process the new PC
				--   ffff (don't care)
				--     read first instruction -> f000 : LDS     #Vec_Default_Stk ;Set up stack pointer
				--   f000 (read 1st instr.; 1st opcode byte)
				--   f001 (read 1st instr.; 2nd opcode byte)
				--   f002 (read 1st instr.; 1st arg byte)
				--     if it's here than we're sure to have a reset/jmp [fffe]
				--   f003 (read 1st instr.; 2nd arg byte)
			
				if i_vec_addr = x"fffe" then
					sig_reset_detect <= "00001";
				elsif i_vec_addr = x"ffff" and sig_reset_detect(0) = '1' then
					sig_reset_detect(0) <= '0';
					sig_reset_detect(1) <= '1';
				elsif i_vec_addr = x"ffff" and sig_reset_detect(1) = '1' then
					sig_reset_detect(1) <= '0';
					sig_reset_detect(2) <= '1';
				elsif i_vec_addr = x"f000" and sig_reset_detect(2) = '1' then
					sig_reset_detect(2) <= '0';
					sig_reset_detect(3) <= '1';
				elsif i_vec_addr = x"f001" and sig_reset_detect(3) = '1' then
					sig_reset_detect(3) <= '0';
					sig_reset_detect(4) <= '1';
				elsif i_vec_addr = x"f002" and sig_reset_detect(4) = '1' then
					sig_mode <= c_mode_bootup;
					sig_master <= '1';
					sig_led <= '1';
				else
					sig_reset_detect <= "00000";
				end if;

			end if;

		end if;
	end process;

end Behavioral;

