/*
 * Copyright (c) 2016. Samsung Electronics Co., LTD
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.samsungxr.io.cursor3d;

import com.samsungxr.SXRContext;
import com.samsungxr.io.SXRCursorController;
import com.samsungxr.utility.Log;

import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;

import java.io.BufferedWriter;
import java.io.IOException;
import java.util.Collections;

class CursorFactory {

    private static final String TAG = CursorFactory.class.getSimpleName();
    // Cursor XML Attributes
    private static final String NAME = "name";
    private static final String TYPE = "type";
    private static final String POSITION = "position";
    private static final String SAVED_VENDOR_ID = "savedIoVendorId";
    private static final String SAVED_PRODUCT_ID = "savedIoProductId";
    private static final String SAVED_DEVICE_ID = "savedIoDeviceId";
    private static final String THEME_ID = "themeId";
    private static final String ACTIVE = "active";

    // Cursor XML elements
    private static final String IO = "io";
    private static final String XML_START_TAG = "<cursor ";
    private static final String XML_END_TAG = "</cursor";

    static Cursor readCursor(XmlPullParser parser, SXRContext context, CursorManager
            cursorManager) throws XmlPullParserException, IOException {
        Cursor cursor;

        String cursorTypeVal = parser.getAttributeValue(XMLUtils.DEFAULT_XML_NAMESPACE, TYPE);
        if (cursorTypeVal == null) {
            throw new XmlPullParserException("No Cursor type specified");
        }
        CursorType cursorType = XMLUtils.getEnumFromString(CursorType.class, cursorTypeVal);
        if (cursorType == CursorType.LASER) {
            cursor = new LaserCursor(context, cursorManager);
        } else if (cursorType == CursorType.OBJECT) {
            cursor = new ObjectCursor(context, cursorManager);
        } else {
            throw new XmlPullParserException("Cannot instantiate Unknown cursor type");
        }

        String vendorId = parser.getAttributeValue(XMLUtils.DEFAULT_XML_NAMESPACE, SAVED_VENDOR_ID);
        String productId = parser.getAttributeValue(XMLUtils.DEFAULT_XML_NAMESPACE,
                SAVED_PRODUCT_ID);
        String savedIoDeviceId = parser.getAttributeValue(XMLUtils.DEFAULT_XML_NAMESPACE,
                SAVED_DEVICE_ID);
        int savedIoVendorId = 0, savedIoProductId = 0;
        boolean savedIoDeviceAvailable = false;
        if (savedIoDeviceId == null || vendorId == null || productId == null) {
            Log.d(TAG, "SavedIoDevice not specified");
            cursor.setSavedController(null);
        } else {
            try {
                savedIoVendorId = Integer.parseInt(vendorId);
                savedIoProductId = Integer.parseInt(productId);
                savedIoDeviceAvailable = true;
            } catch (NumberFormatException e) {
                throw new XmlPullParserException("savedIoVendorId and savedIoProductId should be " +
                        "Integers");
            }
        }

        readOtherCursorAttributes(parser, cursor);

        while (parser.next() != XmlPullParser.END_TAG) {
            if (parser.getEventType() == XmlPullParser.TEXT) {
                continue;
            } else if (parser.getEventType() != XmlPullParser.START_TAG) {
                throw new XmlPullParserException("Cannot find start tag");
            }
            String name = parser.getName();
            Log.d(TAG, "Reading tag:" + name);
            // Starts by looking for the entry tag
            if (name.equals(IO)) {
                //TODO check if priority is repeated
                cursor.getControllers().add(IoDeviceFactory.readIoDeviceFromSettingsXml(parser));
            } else {
                throw new XmlPullParserException("Illegal start tag inside theme");
            }
        }

        if (savedIoDeviceAvailable) {
            for (IODevice tuple : cursor.getControllers()) {
                SXRCursorController controller = tuple.getController();
                if ((controller != null) &&
                    (controller.getVendorId() == savedIoVendorId) &&
                    (controller.getProductId() == savedIoProductId) &&
                    (controller.getName().equals(savedIoDeviceId)))
                {
                    cursor.setSavedController(controller);
                    break;
                }
            }
        }

        Collections.sort(cursor.getControllers());
        return cursor;
    }


    private static void readOtherCursorAttributes(XmlPullParser parser, Cursor cursor) throws
            XmlPullParserException, IOException {
        cursor.setName(parser.getAttributeValue(XMLUtils.DEFAULT_XML_NAMESPACE, NAME));
        if (cursor.getName() == null) {
            throw new XmlPullParserException("Name for cursor not specified");
        }

        String position = parser.getAttributeValue(XMLUtils.DEFAULT_XML_NAMESPACE, POSITION);
        if (position == null) {
            cursor.setStartPosition(Cursor.Position.CENTER);
        } else {
            cursor.setStartPosition(XMLUtils.getEnumFromString(Cursor.Position.class, position));
        }

        String active = parser.getAttributeValue(XMLUtils.DEFAULT_XML_NAMESPACE, ACTIVE);
        if (active == null) {
            throw new XmlPullParserException("active value for cursor is not specified");
        }
        cursor.setEnable(XMLUtils.parseBoolean(active));

        String themeId = parser.getAttributeValue(XMLUtils.DEFAULT_XML_NAMESPACE, THEME_ID);
        if (themeId == null) {
            throw new XmlPullParserException("themeId for cursor is not specified");
        }
        cursor.setSavedThemeId(themeId);
    }

    static void writeCursor(Cursor cursor, BufferedWriter writer) throws IOException
    {
        writer.write(XML_START_TAG);
        // append attributes
        XMLUtils.writeXmlAttribute(NAME, cursor.getName(), writer);
        XMLUtils.writeXmlAttribute(TYPE, cursor.getCursorType(), writer);

        SXRCursorController controller = cursor.getController();
        if (controller != null)
        {
            XMLUtils.writeXmlAttribute(SAVED_VENDOR_ID, controller.getVendorId(), writer);
            XMLUtils.writeXmlAttribute(SAVED_PRODUCT_ID, controller.getProductId(), writer);
            XMLUtils.writeXmlAttribute(SAVED_DEVICE_ID, controller.getName(), writer);
        }
        XMLUtils.writeXmlAttribute(POSITION, cursor.getStartPosition(), writer);
        XMLUtils.writeXmlAttribute(ACTIVE, XMLUtils.xmlFromBoolean(cursor.isEnabled()), writer);
        CursorTheme cursorTheme = cursor.getCursorTheme();
        String savedThemeId = cursor.clearSavedThemeId();
        if (cursorTheme != null)
        {
            XMLUtils.writeXmlAttribute(THEME_ID, cursorTheme.getId(), writer);
        }
        else if (savedThemeId != null)
        {
            XMLUtils.writeXmlAttribute(THEME_ID, savedThemeId, writer);
        }
        else
        {
            throw new RuntimeException("Need a themeId for saving cursor state");
        }

        writer.write(XMLUtils.CLOSING_BRACE);

        for (IODevice tuple : cursor.getControllers())
        {
            IoDeviceFactory.writeIoDevice(tuple, writer, tuple.getPriority());
        }

        writer.write(XML_END_TAG);
        writer.write(XMLUtils.CLOSING_BRACE);
    }
}
