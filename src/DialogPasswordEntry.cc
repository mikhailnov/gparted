/* Copyright (C) 2017 Mike Fleetwood
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "DialogPasswordEntry.h"
#include "Partition.h"

#include <glibmm/ustring.h>
#include <gtkmm/box.h>
#include <gtkmm/stock.h>

namespace GParted
{

DialogPasswordEntry::DialogPasswordEntry( const Partition & partition )
{
	this->set_resizable( false );
	this->set_has_separator( false );
	this->set_size_request( 400, -1 );

	/* TO TRANSLATORS: dialog title, looks like   LUKS Passphrase /dev/sda1 */
	this->set_title( String::ucompose( _("LUKS Passphrase %1"), partition.get_path() ) );

	// Separate VBox to hold lines in the dialog.
	Gtk::VBox *vbox( manage( new Gtk::VBox() ) );
	vbox->set_border_width( 5 );
	vbox->set_spacing( 5 );
	get_vbox()->pack_start( *vbox, Gtk::PACK_SHRINK );

	// Line 1: "Enter LUKS passphrase to open /dev/sda1"
	vbox->pack_start( *Utils::mk_label(
			String::ucompose( _("Enter LUKS passphrase to open %1"), partition.get_path() ) ),
			Gtk::PACK_SHRINK );

	// Line 2: "Passphrase: [              ]"
	// (HBox holding prompt and entry box)
	Gtk::HBox *entry_hbox( manage( new Gtk::HBox() ) );
	entry_hbox->pack_start( *Utils::mk_label( "<b>"+ Glib::ustring( _("Passphrase:") ) + "</b>" ) );
	entry = manage( new Gtk::Entry() );
	entry->set_width_chars( 30 );
	entry->set_visibility( false );
	entry->set_activates_default( true );
	entry_hbox->pack_start( *entry );
	vbox->pack_start( *entry_hbox );

	// Line 3: blank
	vbox->pack_start( *Utils::mk_label( "" ) );

	this->add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL );
	this->add_button( _("Unlock"), Gtk::RESPONSE_OK );
	this->set_default_response( Gtk::RESPONSE_OK );
	this->show_all_children();
}

DialogPasswordEntry::~DialogPasswordEntry()
{
}

Glib::ustring DialogPasswordEntry::get_password()
{
	return Glib::ustring( entry->get_text() );
}

} //GParted